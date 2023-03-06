#ifndef WEBSOCKET_SESSION_HPP
#define WEBSOCKET_SESSION_HPP

#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/websocket.hpp>
#include <functional>

namespace beast = boost::beast;             // from <boost/beast.hpp>
namespace http = beast::http;               // from <boost/beast/http.hpp>
namespace websocket = beast::websocket;     // from <boost/beast/websocket.hpp>
using tcp = boost::asio::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

class websocket_session : public std::enable_shared_from_this<websocket_session>
{
    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;
    std::string message;

public:
    // Take ownership of the socket
    explicit websocket_session(tcp::socket&& socket) : ws_(std::move(socket))
    {
    }

    // Start the asynchronous accept operation
    void    do_accept(http::request<http::string_body> req, 
        std::function<void(std::shared_ptr<websocket_session>, beast::error_code ec)> on_accept);
    void    send_message(std::string message);

private:
    void    on_write(beast::error_code ec, std::size_t bytes_transferred);
};

#endif
