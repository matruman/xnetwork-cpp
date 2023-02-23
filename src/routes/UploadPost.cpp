#include "UploadPost.hpp"

using std::string;

UploadPost::UploadPost(ApplicationContext &context) : AbstractRoute(context)
{
}

UploadPost::~UploadPost()
{
}

void    UploadPost::resolve(HttpRequest& req, urls::url_view& params,
                        UserSession& session, send_lambda& send_)
{
    UserDao &userDao = getContext().getUserDao();
    MessageDao &messageDao = getContext().getMessageDao();

    string &body = req.body();
    json::value js = json::parse(body);
    json::string text = js.as_object().at("text").as_string();

    User user = userDao.getById(session.getUserID());
    Message post(0, Integer(session.getUserID()), 0, String(user.getUsername()), String(text.c_str()), 0);
    messageDao.save(post);

    json::object payload;
    payload.emplace("status", true);
    
    send_(success_response(payload, req));
}