#include "GetNewMessages.hpp"

GetNewMessages::GetNewMessages(ApplicationContext &context) : AbstractRoute(context)
{
}

GetNewMessages::~GetNewMessages()
{
}

void    GetNewMessages::resolve(http::request<http::string_body>& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_)
{
    int converser_id = getIntFromUrlView(params, "converser_id");
    int last_message_id = getIntFromUrlView(params, "last_message_id");
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

    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "application/json");
    set_cors(res);
    res.keep_alive(req.keep_alive());
    res.body() = json::serialize(payload);
    res.prepare_payload();
    send_(std::move(res));
}
