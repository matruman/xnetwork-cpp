#include <memory>
#include <vector>
#include <thread>

#include <server/listener.hpp>

#include <routes/AuthCheck.hpp>
#include <routes/AuthRoute.hpp>
#include <routes/GetChatList.hpp>
#include <routes/GetChatMessages.hpp>
#include <routes/GetNewMessages.hpp>
#include <routes/GetOwnPosts.hpp>
#include <routes/GetUserList.hpp>
#include <routes/SendMessageRoute.hpp>
#include <routes/RegistrationRoute.hpp>
#include <routes/UploadPost.hpp>

namespace net = boost::asio;            // from <boost/asio.hpp>

std::unique_ptr<Router>     makeRouter(std::shared_ptr<ApplicationContext> context)
{
    std::unique_ptr<Router> router = std::make_unique<Router>(context);

    router->addRoute("/auth", std::make_unique<AuthRoute>(context));
    router->addRoute("/authCheck", std::make_unique<AuthCheck>(context));
    router->addRoute("/getChatList", std::make_unique<GetChatList>(context));
    router->addRoute("/getChatMessages", std::make_unique<GetChatMessages>(context));
    router->addRoute("/getNewMessages", std::make_unique<GetNewMessages>(context));
    router->addRoute("/getOwnPosts", std::make_unique<GetOwnPosts>(context));
    router->addRoute("/getUserList", std::make_unique<GetUserList>(context));
    router->addRoute("/sendMessage", std::make_unique<SendMessageRoute>(context));
    router->addRoute("/postSend", std::make_unique<UploadPost>(context));
    router->addRoute("/register", std::make_unique<RegistrationRoute>(context));
    return router;
}

int main(int argc, char* argv[])
{
    // Check command line arguments.
    if (argc != 5)
    {
        std::cerr << "Usage: " << argv[0] << " <address> <port> <doc_root> <threads>\n" <<
            "Example:\n" <<
            "    " << argv[0] << " 0.0.0.0 8080 . 1\n";
        return EXIT_FAILURE;
    }
    auto const address = net::ip::make_address(argv[1]);
    auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
    auto const doc_root = std::make_shared<std::string>(argv[3]);
    auto const threads = std::max<int>(1, std::atoi(argv[4]));

    // The io_context is required for all I/O
    net::io_context ioc{threads};

    std::shared_ptr<ApplicationContext> context = std::make_shared<ApplicationContext>();

    // Create and launch a listening port
    std::make_shared<listener>(ioc, tcp::endpoint{address, port},
        doc_root, context, makeRouter(context))->run();

    // Run the I/O service on the requested number of threads
    std::vector<std::thread> v;
    v.reserve(threads - 1);
    for(auto i = threads - 1; i > 0; --i)
        v.emplace_back(
        [&ioc]
        {
            ioc.run();
        });
    ioc.run();

    return EXIT_SUCCESS;
}