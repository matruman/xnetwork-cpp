#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <iostream>

#include "Router.hpp"
#include "utils.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

class session;

class RequestHandler {

private:
    Router  router;

public:

    // Append an HTTP rel-path to a local filesystem path.
    // The returned path is normalized for the platform.
    std::string     path_cat(beast::string_view base, beast::string_view path);

    // Returns a bad request response
    http::response<http::string_body>   bad_request(beast::string_view why, 
        http::request<http::string_body> req);

    // Returns a not found response
    http::response<http::string_body>   not_found(beast::string_view target, 
        http::request<http::string_body> req);

    // Returns a server error response
    http::response<http::string_body>   server_error(beast::string_view what, 
        http::request<http::string_body> req);

    // This function produces an HTTP response for the given
    // request. The type of the response object depends on the
    // contents of the request, so the interface requires the
    // caller to pass a generic lambda for receiving the response.
    void handle_request(const std::string doc_root, http::request<http::string_body>& req, 
        session::send_lambda& send_);

};

#endif