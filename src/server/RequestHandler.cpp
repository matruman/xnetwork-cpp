#include "RequestHandler.hpp"
#include "Session.hpp"
#include "send_lambda.hpp"
#include <boost/url.hpp>
#include <string>
#include <vector>
#include <algorithm>

namespace urls = boost::urls;

using std::string;
using std::vector;

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

// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.
void RequestHandler::handle_request(const std::string doc_root, 
    http::request<http::string_body>& req, send_lambda& send_)
{
    std::cout << "Request handling started\n"; 
    // Make sure we can handle the method
    if( req.method() != http::verb::get && req.method() != http::verb::post)
        return send_(bad_request("Unknown HTTP-method", req));

    urls::url_view params = urls::parse_origin_form(req.target()).value();
    beast::string_view target = params.path();

    // Request path must be absolute and not contain "..".
    if( target.empty() ||
        target[0] != '/' ||
        target.find("..") != beast::string_view::npos)
        return send_(bad_request("Illegal request-target", req));
    
    vector<beast::string_view> allowed{"/auth", "/authCheck", "/register"};

    auto it = req.find("Cookie");
    if (it == req.end() && std::find(allowed.begin(), allowed.end(), target) == allowed.end())
    {
        return send_(unauthorized("Unauthorized", req));
    }
    UserSession session = it == req.end() ? UserSession() : context.getSessionManager().getSession(it->value());
    if (session.isNull() && std::find(allowed.begin(), allowed.end(), target) == allowed.end())
        return send_(unauthorized("Unauthorized", req));

    // Respond to GET request
    try
    {
        router.route(req, params, session, send_);
    }
    catch (std::invalid_argument &ex)
    {
        std::cerr << ex.what() << std::endl;
        return send_(not_found(target, req));
    }
    catch (SAException &ex)
    {
        std::cerr << saStrToStr(ex.ErrMessage()) << std::endl;
        return send_(bad_request(target, req));
    }
    catch (...)
    {
        return send_(server_error(target, req));
    }
}