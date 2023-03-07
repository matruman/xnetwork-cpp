#include "GetChatList.hpp"

GetChatList::GetChatList(std::shared_ptr<ApplicationContext> context) : AbstractRoute(context)
{
}

GetChatList::~GetChatList()
{
}

void    GetChatList::resolve(HttpRequest& req, URLParams& params,
                        UserSession& session, send_lambda& send_)
{
    int offset = std::stoi(params.getParam("offset"));
    vector<Chat> chats = getContext().getChatDao().getChats(session.getUserID().get(), offset);
    json::array chatsJson;
    for (auto &chat : chats)
    {
        chatsJson.emplace_back(chat.getJsonObject());
    }

    json::object payload;
    payload.emplace("status", true);
    payload.emplace("data", chatsJson);

    send_(success_response(payload, req));
}