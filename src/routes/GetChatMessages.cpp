#include "GetChatMessages.hpp"

GetChatMessages::GetChatMessages(ApplicationContext &context) : AbstractRoute(context)
{
}

GetChatMessages::~GetChatMessages()
{
}

void    GetChatMessages::resolve(HttpRequest& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_)
{
    MessageDao &dao = getContext().getMessageDao();
    int converser_id = getIntFromUrlView(params, "converser_id");
    int offset = getIntFromUrlView(params, "offset");
    
    vector<Message> messages = dao.getChatMessages(session.getUserID().get(), converser_id, offset);
    json::array jsonMessages;
    for (auto &msg : messages)
    {
        jsonMessages.emplace_back(msg.getJsonObject());
    }

    json::object payload;
    payload.emplace("status", true);
    payload.emplace("data", jsonMessages);

    send_(success_response(payload, req));
}