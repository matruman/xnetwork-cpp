#ifndef UTILS_HPP
#define UTILS_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include <winsock2.h>
#include <boost/beast/version.hpp>
#include <boost/url/url_view.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <SQLAPI.h>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace urls = boost::urls;           // from <boost/url.hpp>
namespace json = boost::json;

using std::string;

// // Return a reasonable mime type based on the extension of a file.
// beast::string_view  mime_type(beast::string_view path);

// Set CORS headers to request.
void            set_cors(HttpResponse &res);

// Returns a success response
HttpResponse    success_response(json::object &payload, HttpRequest &req);

// Returns a bad request response
HttpResponse    bad_request(string why, HttpRequest &req);

// Returns a not found response
HttpResponse    not_found(string target, HttpRequest &req);

// Returns an unauthorized response
HttpResponse    unauthorized(string what, HttpRequest &req);

// Returns a server error response
HttpResponse    server_error(string what, HttpRequest &req);

int             getIntFromUrlView(urls::url_view& params, std::string name);
std::string     getStringFromUrlView(urls::url_view& params, std::string name);


#endif