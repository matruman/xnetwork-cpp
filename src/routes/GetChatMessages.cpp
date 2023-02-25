#include "GetChatMessages.hpp"

GetChatMessages::GetChatMessages(ApplicationContext &context) : AbstractRoute(context)
{
}

GetChatMessages::~GetChatMessages()
{
}

void    GetChatMessages::resolve(HttpRequest& req, URLParams& params,
                        UserSession& session, send_lambda& send_)
{
    MessageDao &dao = getContext().getMessageDao();
    int converser_id = std::stoi(params.getParam("converser_id"));
    int offset = std::stoi(params.getParam("offset"));
    
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