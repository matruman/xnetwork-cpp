#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include <winsock2.h>
#include "HttpRequest.hpp"
#include <iostream>

#include <application/ApplicationContext.hpp>
#include <application/SessionManager.hpp>
#include "Router.hpp"
#include "send_lambda.hpp"
#include "utils.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

class RequestHandler {

private:
    ApplicationContext &context;
    Router  router;

public:
    RequestHandler(ApplicationContext &context);

    // Append an HTTP rel-path to a local filesystem path.
    // The returned path is normalized for the platform.
    std::string     path_cat(string base, string path);

    // This function produces an HTTP response for the given
    // request. The type of the response object depends on the
    // contents of the request, so the interface requires the
    // caller to pass a generic lambda for receiving the response.
    void    handle_request(const std::string doc_root, 
        HttpRequest& req, send_lambda& send_);
    void    handle_ws_upgrade(std::shared_ptr<websocket_session> wss, HttpRequest& req);
};

#endif