#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include <boost/beast/http.hpp>
#include <iostream>

#include "SessionManager.hpp"
#include "Router.hpp"
#include "ApplicationContext.hpp"
#include "send_lambda.hpp"
#include "utils.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

class session;

class RequestHandler {

private:
    ApplicationContext &context;
    Router  router;

public:
    RequestHandler(ApplicationContext &context);

    // Append an HTTP rel-path to a local filesystem path.
    // The returned path is normalized for the platform.
    std::string     path_cat(beast::string_view base, beast::string_view path);

    // This function produces an HTTP response for the given
    // request. The type of the response object depends on the
    // contents of the request, so the interface requires the
    // caller to pass a generic lambda for receiving the response.
    void handle_request(const std::string doc_root, http::request<http::string_body>& req, 
        send_lambda& send_);
};

#endif