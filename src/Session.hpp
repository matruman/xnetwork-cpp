#ifndef SESSION_HPP
#define SESSION_HPP

#include "utils.hpp"
#include <boost/asio/dispatch.hpp>
#include <memory>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class RequestHandler;

// Handles an HTTP server connection
class session : public std::enable_shared_from_this<session>
{
public:
    // This is the C++11 equivalent of a generic lambda.
    // The function object is used to send an HTTP message.
    struct send_lambda
    {
        session& self_;

        explicit send_lambda(session& self) : self_(self)
        {}

        template<class Body>
        void operator()(http::response<Body>&& resp) const
        {
            // The lifetime of the message has to extend
            // for the duration of the async operation so
            // we use a shared_ptr to manage it.
            auto sp = std::make_shared<http::response<Body>>(std::move(resp));

            // Store a type-erased version of the shared
            // pointer in the class to keep it alive.
            self_.res_ = sp;

            // Write the response
            http::async_write(
                self_.stream_,
                *sp,
                beast::bind_front_handler(
                    &session::on_write,
                    self_.shared_from_this(),
                    sp->need_eof()));
        }
    };

private:
    RequestHandler &handler;
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_;
    std::shared_ptr<std::string const> doc_root_;
    http::request<http::string_body> req_;
    std::shared_ptr<void> res_;
    send_lambda lambda_;

public:
    // Take ownership of the stream
    session(RequestHandler &handler, tcp::socket&& socket, 
        std::shared_ptr<std::string const> const& doc_root);

    void    run();
    void    do_read();
    void    on_read(beast::error_code ec, std::size_t bytes_transferred);
    void    on_write(bool close, beast::error_code ec, std::size_t bytes_transferred);
    void    do_close();
};

#endif