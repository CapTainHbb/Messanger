cmake_minimum_required(VERSION 3.25)

project(XmppServer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(XmppServer main.cpp XmppServer.cpp
        XmppServerExtensionRosterHandler.cpp
        XmppServerExtensionRosterHandler.hpp)

target_link_libraries(XmppServer PRIVATE  Qt6::Core Qt6::Network QXmpp::QXmpp ${QXMPP_TARGET})
