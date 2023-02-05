#include "UploadPost.hpp"

using std::string;

UploadPost::UploadPost(ApplicationContext &context) : AbstractRoute(context)
{
}

UploadPost::~UploadPost()
{
}

void    UploadPost::resolve(http::request<http::string_body>& req,
                                    session::send_lambda& send_)
{
    UserDao &userDao = getContext().getUserDao();
    MessageDao &messageDao = getContext().getMessageDao();

    string &body = req.body();
    json::value js = json::parse(body);
    json::string text = js.as_object().at("text").as_string();

    User user = userDao.getById(1);
    Message post(0, 1, 0, String(user.getUsername()), String(text.c_str()), 0);
    messageDao.save(post);

    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "application/json");
    res.set(http::field::access_control_allow_origin, "http://localhost:3000");
    res.set(http::field::access_control_allow_credentials, "true");
    res.keep_alive(req.keep_alive());
    res.body() = "{ \"status\" : \"ok\" }";
    res.prepare_payload();
    send_(std::move(res));
}