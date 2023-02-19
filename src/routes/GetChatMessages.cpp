#include "GetChatMessages.hpp"

GetChatMessages::GetChatMessages(ApplicationContext &context) : AbstractRoute(context)
{
}

GetChatMessages::~GetChatMessages()
{
}

void    GetChatMessages::resolve(http::request<http::string_body>& req, urls::url_view& params,
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

    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "application/json");
    set_cors(res);
    res.keep_alive(req.keep_alive());
    res.body() = json::serialize(payload);
    res.prepare_payload();
    send_(std::move(res));
}