#include "SendMessageRoute.hpp"

SendMessageRoute::SendMessageRoute(ApplicationContext &context) : AbstractRoute(context)
{
}

SendMessageRoute::~SendMessageRoute()
{
}

void    SendMessageRoute::resolve(http::request<http::string_body>& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_)
{
    string &body = req.body();
    json::value js = json::parse(body);
    json::string text = js.as_object().at("text").as_string();
    int converser_id = js.as_object().at("converser_id").as_int64();

    if (!getContext().getChatDao().existsChat(session.getUserID(), converser_id))
    {
        getContext().getChatDao().createChat(session.getUserID(), converser_id);
    }

    Message message(
        0,
        session.getUserID().get(),
        converser_id,
        String(),
        String(text.c_str()),
        0
    );  
    Integer message_id = getContext().getMessageDao().save(message);
    
    json::object payload;
    payload.emplace("status", true);
    
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "application/json");
    set_cors(res);
    res.keep_alive(req.keep_alive());
    res.body() = json::serialize(payload);
    res.prepare_payload();
    send_(std::move(res));
}