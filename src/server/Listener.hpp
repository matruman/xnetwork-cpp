#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/strand.hpp>

#include "utils.hpp"
#include "session.hpp"
#include "RequestHandler.hpp"
#include <application/ApplicationContext.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

// Accepts incoming connections and launches the sessions
class listener : public std::enable_shared_from_this<listener>
{
    net::io_context& ioc_;
    tcp::acceptor acceptor_;
    std::shared_ptr<std::string const> doc_root_;
    RequestHandler handler;

public:
    listener(net::io_context& ioc, tcp::endpoint endpoint, 
        std::shared_ptr<std::string const> const& doc_root,
        std::shared_ptr<ApplicationContext> context_,
        std::unique_ptr<Router> &&router_);

    // Start accepting incoming connections
    void    run();

private:
    void    do_accept();
    void    on_accept(beast::error_code ec, tcp::socket socket);
};

#endif