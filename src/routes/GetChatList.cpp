#include "GetChatList.hpp"

GetChatList::GetChatList(ApplicationContext &context) : AbstractRoute(context)
{
}

GetChatList::~GetChatList()
{
}

void    GetChatList::resolve(HttpRequest& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_)
{
    int offset = getIntFromUrlView(params, "offset");
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