cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../)
include_directories(proxy_models/)

add_library(model 
    GeneralModel.hpp GeneralModel.cpp
    proxy_models/GeneralProxyModel.hpp proxy_models/GeneralProxyModel.cpp
    proxy_models/ContactProxyModel.hpp proxy_models/ContactProxyModel.cpp
    proxy_models/ChatListProxyModel.hpp proxy_models/ChatListProxyModel.cpp
    proxy_models/ActiveChatProxyModel.hpp proxy_models/ActiveChatProxyModel.cpp
    Contact.hpp Contact.cpp
    Chat.hpp Chat.cpp
)

target_link_libraries(model PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Test
    Qt5::Widgets
)
