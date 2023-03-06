#include "send_lambda.hpp"
#include "session.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>


void    send_lambda::operator()(HttpResponse&& resp) const
{
    // The lifetime of the message has to extend
    // for the duration of the async operation so
    // we use a shared_ptr to manage it.
    
    // Move response to the session object field
    self_.getRes() = std::move(resp);

    // Write the response
    http::async_write(
        self_.getStream(),
        *self_.getRes().get(),
        beast::bind_front_handler(
            &session::on_write,
            self_.shared_from_this(),
            self_.getRes().get()->need_eof()));
}