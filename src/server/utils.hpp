#ifndef UTILS_HPP
#define UTILS_HPP

#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/url/url_view.hpp>
#include <iostream>
#include <SQLAPI.h>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace urls = boost::urls;           // from <boost/url.hpp>

using std::string;

// Report a failure
void    fail(beast::error_code ec, char const* what);

// Return a reasonable mime type based on the extension of a file.
beast::string_view  mime_type(beast::string_view path);

// Set CORS headers to request.
void    set_cors(http::response<http::string_body>& res);

// Returns a bad request response
http::response<http::string_body>   bad_request(beast::string_view why, 
    http::request<http::string_body> req);

// Returns a not found response
http::response<http::string_body>   not_found(beast::string_view target, 
    http::request<http::string_body> req);

// Returns an unauthorized response
http::response<http::string_body>   unauthorized(beast::string_view what, 
    http::request<http::string_body> req);

// Returns a server error response
http::response<http::string_body>   server_error(beast::string_view what, 
    http::request<http::string_body> req);

int             getIntFromUrlView(urls::url_view& params, std::string name);
std::string     getStringFromUrlView(urls::url_view& params, std::string name);


#endif