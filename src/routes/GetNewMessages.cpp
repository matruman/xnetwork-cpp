#include "GetNewMessages.hpp"

GetNewMessages::GetNewMessages(ApplicationContext &context) : AbstractRoute(context)
{
}

GetNewMessages::~GetNewMessages()
{
}

void    GetNewMessages::resolve(HttpRequest& req, URLParams& params,
                        UserSession& session, send_lambda& send_)
{
    int converser_id = std::stoi(params.getParam("converser_id"));
    int last_message_id = std::stoi(params.getParam("last_message_id"));
    vector<Message> messages = getContext().getMessageDao().getNewMessages(session.getUserID().get(),
        converser_id, last_message_id);
    json::array messagesJson;
    for (auto &msg : messages)
    {
        messagesJson.emplace_back(msg.getJsonObject());
    }

    json::object payload;
    payload.emplace("status", true);
    payload.emplace("data", messagesJson);

    send_(success_response(payload, req));
}
