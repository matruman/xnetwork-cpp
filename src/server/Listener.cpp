#include "listener.hpp"

listener::listener(net::io_context& ioc, tcp::endpoint endpoint, 
    std::shared_ptr<std::string const> const& doc_root,
    std::shared_ptr<ApplicationContext> context_,
    std::unique_ptr<Router> &&router_)
    : ioc_(ioc), acceptor_(net::make_strand(ioc)),
        doc_root_(doc_root), handler(context_, std::move(router_))
{
    beast::error_code ec;

    // Open the acceptor
    acceptor_.open(endpoint.protocol(), ec);
    if(ec)
    {
        session::fail(ec, "open");
        return;
    }

    // Allow address reuse
    acceptor_.set_option(net::socket_base::reuse_address(true), ec);
    if(ec)
    {
        session::fail(ec, "set_option");
        return;
    }

    // Bind to the server address
    acceptor_.bind(endpoint, ec);
    if(ec)
    {
        session::fail(ec, "bind");
        return;
    }

    // Start listening for connections
    acceptor_.listen(
        net::socket_base::max_listen_connections, ec);
    if(ec)
    {
        session::fail(ec, "listen");
        return;
    }
}

void    listener::run()
{
    std::cout << "Listener started" << std::endl;
    do_accept();
}

void    listener::do_accept()
{
    // The new connection gets its own strand
    acceptor_.async_accept(
        net::make_strand(ioc_),
        beast::bind_front_handler(
            &listener::on_accept,
            shared_from_this()));
}

void    listener::on_accept(beast::error_code ec, tcp::socket socket)
{
    if(ec)
    {
        session::fail(ec, "accept");
        return; // To avoid infinite loop
    }
    else
    {
        // Create the session and run it
        std::make_shared<session>(handler, std::move(socket), doc_root_)->run();
    }

    // Accept another connection
    do_accept();
}