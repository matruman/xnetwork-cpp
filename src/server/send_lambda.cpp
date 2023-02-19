#include "send_lambda.hpp"
#include "Session.hpp"

void    send_lambda::operator()(http::response<http::string_body>&& resp) const
{
    // The lifetime of the message has to extend
    // for the duration of the async operation so
    // we use a shared_ptr to manage it.
    auto sp = std::make_shared<http::response<http::string_body>>(std::move(resp));

    // Store a type-erased version of the shared
    // pointer in the class to keep it alive.
    self_.getRes() = sp;

    // Write the response
    http::async_write(
        self_.getStream(),
        *sp,
        beast::bind_front_handler(
            &session::on_write,
            self_.shared_from_this(),
            sp->need_eof()));
}