#include "utils.hpp"

// // Return a reasonable mime type based on the extension of a file.
// beast::string_view  mime_type(beast::string_view path)
// {
//     using beast::iequals;
//     auto const ext = [&path]
//     {
//         auto const pos = path.rfind(".");
//         if(pos == beast::string_view::npos)
//             return beast::string_view{};
//         return path.substr(pos);
//     }();
//     if(iequals(ext, ".htm"))  return "text/html";
//     if(iequals(ext, ".html")) return "text/html";
//     if(iequals(ext, ".php"))  return "text/html";
//     if(iequals(ext, ".css"))  return "text/css";
//     if(iequals(ext, ".txt"))  return "text/plain";
//     if(iequals(ext, ".js"))   return "application/javascript";
//     if(iequals(ext, ".json")) return "application/json";
//     if(iequals(ext, ".xml"))  return "application/xml";
//     if(iequals(ext, ".swf"))  return "application/x-shockwave-flash";
//     if(iequals(ext, ".flv"))  return "video/x-flv";
//     if(iequals(ext, ".png"))  return "image/png";
//     if(iequals(ext, ".jpe"))  return "image/jpeg";
//     if(iequals(ext, ".jpeg")) return "image/jpeg";
//     if(iequals(ext, ".jpg"))  return "image/jpeg";
//     if(iequals(ext, ".gif"))  return "image/gif";
//     if(iequals(ext, ".bmp"))  return "image/bmp";
//     if(iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
//     if(iequals(ext, ".tiff")) return "image/tiff";
//     if(iequals(ext, ".tif"))  return "image/tiff";
//     if(iequals(ext, ".svg"))  return "image/svg+xml";
//     if(iequals(ext, ".svgz")) return "image/svg+xml";
//     return "application/text";
// }

void    set_cors(HttpResponse &res)
{
    res.set("Access-Control-Allow-Origin", "http://192.168.1.64:3000");
    res.set("Access-Control-Allow-Credentials", "true");
}

// Returns a success response
HttpResponse    success_response(json::object &payload, HttpRequest &req)
{
    HttpResponse res(HttpResponse::ok, req.version());
    res.set("Server", BOOST_BEAST_VERSION_STRING);
    res.set("Content-Type", "application/json");
    set_cors(res);
    res.keep_alive(req.keep_alive());
    res.body() = json::serialize(payload);
    res.prepare_payload();
    return res;
}

// Returns a bad request response
HttpResponse    bad_request(string why, HttpRequest &req)
{
    HttpResponse res(HttpResponse::bad_request, req.version());
    res.set("Server", BOOST_BEAST_VERSION_STRING);
    res.set("Content-Type", "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = std::string(why);
    res.prepare_payload();
    return res;
}

// Returns a not found response
HttpResponse   not_found(string target, HttpRequest &req)
{
    std::cout << "not found\n";
    HttpResponse res(HttpResponse::not_found, req.version());
    res.set("Server", BOOST_BEAST_VERSION_STRING);
    res.set("Content-Type", "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = "The resource '" + std::string(target) + "' was not found.";
    res.prepare_payload();
    std::cout << "not found1\n";
    return res;
}

// Returns an unauthorized response
HttpResponse   unauthorized(string what, HttpRequest &req)
{
    HttpResponse res(HttpResponse::unauthorized, req.version());
    res.set("Server", BOOST_BEAST_VERSION_STRING);
    res.set("Content-Type", "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = "An error occurred: '" + std::string(what) + "'";
    res.prepare_payload();
    return res;
}

// Returns a server error response
HttpResponse   server_error(string what, HttpRequest &req)
{
    HttpResponse res(HttpResponse::internal_server_error, req.version());
    res.set("Server", BOOST_BEAST_VERSION_STRING);
    res.set("Content-Type", "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = "An error occurred: '" + what + "'";
    res.prepare_payload();
    return res;
}

// int     getIntFromUrlView(urls::url_view &params, std::string name)
// {
//     auto it = params.params().find(name);
//     return std::stoi((*it).value);
// }

// std::string     getStringFromUrlView(urls::url_view &params, std::string name)
// {
//      auto it = params.params().find(name);
//     return (*it).value;
// }
