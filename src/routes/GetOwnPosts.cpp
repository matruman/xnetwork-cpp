#include "GetOwnPosts.hpp"
#include <entities/message/MessageDao.hpp>

GetOwnPosts::GetOwnPosts(std::shared_ptr<ApplicationContext> context) : AbstractRoute(context)
{
}

GetOwnPosts::~GetOwnPosts()
{
}

void    GetOwnPosts::resolve(HttpRequest& req, URLParams& params,
                        UserSession& session, send_lambda& send_)
{
    MessageDao &dao = getContext().getMessageDao();
    string tmp = params.getParam("offset");
    int offset = std::stoi(tmp);
    
    vector<Message> posts = dao.getUserPosts(session.getUserID().get(), offset);
    json::array postsJson;
    for (auto &post : posts)
    {
        postsJson.emplace_back(post.getJsonObject());
    }

    json::object payload;
    payload.emplace("status", true);
    payload.emplace("data", postsJson);

    send_(success_response(payload, req));
}