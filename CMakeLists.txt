cmake_minimum_required(VERSION 3.12)

project(xnetwork)

set(EXECUTABLE_NAME server)

SET(CMAKE_CXX_FLAGS "-std=c++11 -g -Og")

find_package(Boost REQUIRED COMPONENTS json)
include_directories(
	${Boost_INCLUDE_DIRS}
	"C:/SQLAPI/mingw-w64/include"
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/src"
)

link_directories("C:/SQLAPI/mingw-w64/lib" "C:/SQLAPI/mingw-w64/bin")

add_executable(${EXECUTABLE_NAME}

	src/datatypes/datatypes.cpp
	src/datatypes/datatypes.hpp
	
	src/entities/chat/Chat.cpp
	src/entities/chat/Chat.hpp
	src/entities/chat/ChatDao.cpp
	src/entities/chat/ChatDao.hpp
	src/entities/message/Message.cpp
	src/entities/message/Message.hpp
	src/entities/message/MessageDao.cpp
	src/entities/message/MessageDao.hpp
	src/entities/subscription/Subscription.cpp
	src/entities/subscription/Subscription.hpp
	src/entities/subscription/SubscriptionDao.cpp
	src/entities/subscription/SubscriptionDao.hpp
	src/entities/user/User.cpp
	src/entities/user/User.hpp
	src/entities/user/UserDao.cpp
	src/entities/user/UserDao.hpp
	
	src/routes/AbstractRoute.cpp
	src/routes/AbstractRoute.hpp
	src/routes/DefaultRoute.cpp
	src/routes/DefaultRoute.hpp
	src/routes/GetOwnPosts.cpp
	src/routes/GetOwnPosts.hpp
	src/routes/UploadPost.cpp
	src/routes/UploadPost.hpp
	
	src/server/ApplicationContext.cpp
	src/server/ApplicationContext.hpp
	src/server/Listener.cpp
	src/server/Listener.hpp
	src/server/RequestHandler.cpp
	src/server/RequestHandler.hpp
	src/server/Router.cpp
	src/server/Router.hpp
	src/server/Session.cpp
	src/server/Session.hpp
	src/server/utils.cpp
	src/server/utils.hpp

	src/main.cpp
)

target_link_libraries(${EXECUTABLE_NAME} sqlapiu)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_link_libraries(${EXECUTABLE_NAME} pthread)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_link_libraries(${EXECUTABLE_NAME} 
		Boost::boost
		Boost::json
		wsock32
		ws2_32
		Version
	)
endif()
