#include "GetUserList.hpp"

GetUserList::GetUserList(ApplicationContext &context) : AbstractRoute(context)
{
}

GetUserList::~GetUserList()
{
}

void    GetUserList::resolve(HttpRequest& req, URLParams& params,
                        UserSession& session, send_lambda& send_)
{    
    string &body = req.body();
    std::cout << body << std::endl;
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

    send_(success_response(payload, req));
}