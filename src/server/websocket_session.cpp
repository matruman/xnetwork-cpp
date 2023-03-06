#include "websocket_session.hpp"
#include <iostream>
#include <boost/bind/bind.hpp>

// Report a failure
static void    fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

// Start the asynchronous accept operation
void    websocket_session::do_accept(http::request<http::string_body> req, 
    std::function<void(std::shared_ptr<websocket_session>, beast::error_code ec)> on_accept)
{
    // Set suggested timeout settings for the websocket
    ws_.set_option(
        websocket::stream_base::timeout::suggested(
            beast::role_type::server));

    // Set a decorator to change the Server of the handshake
    ws_.set_option(websocket::stream_base::decorator(
        [](websocket::response_type& res)
        {
            res.set(http::field::server,
                std::string(BOOST_BEAST_VERSION_STRING) +
                    " advanced-server");
        }));
    
    // Accept the websocket handshake
    ws_.async_accept(req, beast::bind_front_handler(on_accept, shared_from_this()));
}

void    websocket_session::send_message(std::string msg)
{
    // Save the message in this object
    message = msg;
    ws_.async_write(
        boost::asio::const_buffer(message.c_str(), message.length()),
        beast::bind_front_handler(
            &websocket_session::on_write,
            shared_from_this()));
}

void    websocket_session::on_write(
    beast::error_code ec,
    std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec)
        return fail(ec, "write");

    // Clear the buffer
    buffer_.consume(buffer_.size());

    // Do another read
}