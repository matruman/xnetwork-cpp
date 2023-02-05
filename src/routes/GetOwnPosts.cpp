#include "GetOwnPosts.hpp"
#include <boost/json.hpp>
#include <entities/message/MessageDao.hpp>
#include <vector>

using std::string;
using std::vector;
namespace json = boost::json;

GetOwnPosts::GetOwnPosts(ApplicationContext &context) : AbstractRoute(context)
{
}

GetOwnPosts::~GetOwnPosts()
{
}

void    GetOwnPosts::resolve(http::request<http::string_body>& req,
                                    session::send_lambda& send_)
{
    MessageDao &dao = getContext().getMessageDao(); 
    
    vector<Message> posts = dao.getUserPosts(1);
    json::array postsJson;
    for (auto &post : posts)
    {
        postsJson.emplace_back(post.getJsonObject());
    }
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "application/json");
    res.set(http::field::access_control_allow_origin, "http://localhost:3000");
    res.set(http::field::access_control_allow_credentials, "true");
    res.keep_alive(req.keep_alive());
    res.body() = json::serialize(postsJson);
    res.prepare_payload();
    send_(std::move(res));
}