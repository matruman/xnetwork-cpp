#include "SendMessageRoute.hpp"

SendMessageRoute::SendMessageRoute(std::shared_ptr<ApplicationContext> context) : AbstractRoute(context)
{
}

SendMessageRoute::~SendMessageRoute()
{
}

void    SendMessageRoute::resolve(HttpRequest& req, URLParams& params,
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
    payload.emplace("message_id", message_id.get());

    UserSession &reseiverSession = getContext().getSessionManager().getSessionByUserID(converser_id);
    
    json::object notification;
    notification.emplace("type", "message");
    notification.emplace("sender_id", session.getUserID());
    if (!reseiverSession.isNull())
        reseiverSession.sendMessage(json::serialize(notification));
    
    send_(success_response(payload, req));
}