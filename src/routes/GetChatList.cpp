#include "GetChatList.hpp"

GetChatList::GetChatList(ApplicationContext &context) : AbstractRoute(context)
{
}

GetChatList::~GetChatList()
{
}

void    GetChatList::resolve(http::request<http::string_body>& req, urls::url_view& params,
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

    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "application/json");
    set_cors(res);
    res.keep_alive(req.keep_alive());
    res.body() = json::serialize(payload);
    res.prepare_payload();
    send_(std::move(res));
}