#ifndef SESSION_HPP
#define SESSION_HPP

#include "HttpRequest.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <memory>

#include "utils.hpp"
#include "send_lambda.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class RequestHandler;

// Handles an HTTP server connection
class session : public std::enable_shared_from_this<session>
{    
private:
    RequestHandler &handler;
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_;
    std::shared_ptr<std::string const> doc_root_;
    HttpRequest req_;
    HttpResponse res_;
    send_lambda lambda_;

public:
    // Take ownership of the stream
    session(RequestHandler &handler, tcp::socket&& socket, 
        std::shared_ptr<std::string const> const& doc_root);

    static void    fail(beast::error_code ec, char const* what);

    void    run();
    void    do_read();
    void    on_read(beast::error_code ec, std::size_t bytes_transferred);
    void    on_write(bool close, beast::error_code ec, std::size_t bytes_transferred);
    void    do_close();

    beast::tcp_stream&      getStream() { return stream_; }
    HttpResponse&  getRes() { return res_; }    
};

#endif