#ifndef UTILS_HPP
#define UTILS_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include <boost/beast/version.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <SQLAPI.h>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace json = boost::json;

using std::string;


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

// int             getIntFromUrlView(urls::url_view& params, std::string name);
// std::string     getStringFromUrlView(urls::url_view& params, std::string name);


#endif