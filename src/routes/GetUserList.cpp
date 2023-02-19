#include "GetUserList.hpp"

GetUserList::GetUserList(ApplicationContext &context) : AbstractRoute(context)
{
}

GetUserList::~GetUserList()
{
}

void    GetUserList::resolve(http::request<http::string_body>& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_)
{    
    string &body = req.body();
    json::value js = json::parse(body);
    json::string username = js.as_object().at("username").as_string();
    int offset = js.as_object().at("offset").as_int64();

    vector<UserListElem> users = getContext().getUserDao().findUsers(username.c_str(), offset);
    json::array usersJson;
    for (auto &user : users)
    {
        usersJson.emplace_back(user.getJsonObject());
    }

    json::object payload;
    payload.emplace("status", true);
    payload.emplace("data", usersJson);

    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "application/json");
    set_cors(res);
    res.keep_alive(req.keep_alive());
    res.body() = json::serialize(payload);
    res.prepare_payload();
    send_(std::move(res));
}