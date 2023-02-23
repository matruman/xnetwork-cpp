#include "GetOwnPosts.hpp"
#include <entities/message/MessageDao.hpp>

GetOwnPosts::GetOwnPosts(ApplicationContext &context) : AbstractRoute(context)
{
}

GetOwnPosts::~GetOwnPosts()
{
}

void    GetOwnPosts::resolve(HttpRequest& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_)
{
    MessageDao &dao = getContext().getMessageDao();
    int offset = getIntFromUrlView(params, "offset");
    
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