#include "RequestHandler.hpp"
#include "Session.hpp"

RequestHandler::RequestHandler(ApplicationContext &context_) : context(context_), router(context_)
{
}

// Append an HTTP rel-path to a local filesystem path.
// The returned path is normalized for the platform.
std::string     RequestHandler::path_cat(beast::string_view base, beast::string_view path)
{
    if(base.empty())
        return std::string(path);
    std::string result(base);
#ifdef BOOST_MSVC
    char constexpr path_separator = '\\';
    if(result.back() == path_separator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());
    for(auto& c : result)
        if(c == '/')
            c = path_separator;
#else
    char constexpr path_separator = '/';
    if(result.back() == path_separator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());
#endif
    return result;
}

// Returns a bad request response
http::response<http::string_body>   RequestHandler::bad_request(beast::string_view why, 
    http::request<http::string_body> req)
{
    http::response<http::string_body> res{http::status::bad_request, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = std::string(why);
    res.prepare_payload();
    return res;
}

// Returns a not found response
http::response<http::string_body>   RequestHandler::not_found(beast::string_view target, 
    http::request<http::string_body> req)
{
    http::response<http::string_body> res{http::status::not_found, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = "The resource '" + std::string(target) + "' was not found.";
    res.prepare_payload();
    return res;
}

// Returns a server error response
http::response<http::string_body>   RequestHandler::server_error(beast::string_view what, 
    http::request<http::string_body> req)
{
    http::response<http::string_body> res{http::status::internal_server_error, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = "An error occurred: '" + std::string(what) + "'";
    res.prepare_payload();
    return res;
}

// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.
void RequestHandler::handle_request(const std::string doc_root, 
    http::request<http::string_body>& req, 
    session::send_lambda& send_)
{
    // Make sure we can handle the method
    if( req.method() != http::verb::get && req.method() != http::verb::post)
        return send_(bad_request("Unknown HTTP-method", req));

    // Request path must be absolute and not contain "..".
    if( req.target().empty() ||
        req.target()[0] != '/' ||
        req.target().find("..") != beast::string_view::npos)
        return send_(bad_request("Illegal request-target", req));

    // // Build the path to the requested file
    // std::string path = path_cat(doc_root, req.target());
    // if(req.target().back() == '/')
    //     path.append("index.html");

    // // Attempt to open the file
    // beast::error_code ec;
    // http::file_body::value_type body;
    // body.open(path.c_str(), beast::file_mode::scan, ec);

    // // Handle the case where the file doesn't exist
    // if(ec == beast::errc::no_such_file_or_directory)
    //     return send_(not_found(req.target(), req));

    // // Handle an unknown error
    // if(ec)
    //     return send_(server_error(ec.message(), req));

    // // Cache the size since we need it after the move
    // auto const size = body.size();

    // Respond to GET request
    try
    {
        router.route(req.target(), req, send_);
    }
    catch (std::invalid_argument &ex)
    {
        std::cerr << ex.what() << std::endl;
        return send_(not_found(req.target(), req));
    }
    catch (SAException &ex)
    {
        std::cerr << saStrToStr(ex.ErrMessage()) << std::endl;
        return send_(not_found(req.target(), req));
    }
}