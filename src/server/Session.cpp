#include "Session.hpp"
#include "RequestHandler.hpp"

session::session(RequestHandler &handler, tcp::socket&& socket, 
    std::shared_ptr<std::string const> const& doc_root) 
    : handler(handler), stream_(std::move(socket)),
        doc_root_(doc_root), lambda_(*this)
{}

// Start the asynchronous operation
void    session::run()
{
    // We need to be executing within a strand to perform async operations
    // on the I/O objects in this session. Although not strictly necessary
    // for single-threaded contexts, this example code is written to be
    // thread-safe by default.
    net::dispatch(stream_.get_executor(),
                    beast::bind_front_handler(
                        &session::do_read,
                        shared_from_this()));
}

// Report a failure
void    session::fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

void    session::do_read()
{
    // Make the request empty before reading,
    // otherwise the operation behavior is undefined.
    req_.clear();

    // Set the timeout.
    stream_.expires_after(std::chrono::seconds(30));

    // Read a request
    http::async_read(stream_, buffer_, *req_.get(),
        beast::bind_front_handler(&session::on_read,shared_from_this()));
}

void    session::on_read(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    // This means they closed the connection
    if(ec == http::error::end_of_stream)
        return do_close();

    if(ec)
        return fail(ec, "read");

    // Send the response
    handler.handle_request(*doc_root_, req_, lambda_);
}

void    session::on_write(bool close, beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec)
        return fail(ec, "write");

    if(close)
    {
        // This means we should close the connection, usually because
        // the response indicated the "Connection: close" semantic.
        return do_close();
    }

    // // We're done with the response so delete it
    // res_ = nullptr;

    // Read another request
    do_read();
}

void    session::do_close()
{
    // Send a TCP shutdown
    beast::error_code ec;
    stream_.socket().shutdown(tcp::socket::shutdown_send, ec);

    // At this point the connection is closed gracefully
}