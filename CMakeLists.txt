cmake_minimum_required(VERSION 3.25)

project(Messanger VERSION 0.1 LANGUAGES CXX)

include(CTest)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QXmpp)
set(QXMPP_TARGET QXmppQt${QT_VERSION_MAJOR})

if(NOT DEFINED QT_VERSION_MAJOR)
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network Xml Widgets Test)
endif()
message("-- Choosing Qt ${QT_VERSION_MAJOR}")
find_package(Qt${QT_VERSION_MAJOR} 5.15.0 REQUIRED COMPONENTS Core Network Xml Widgets Test)

include_directories(widgets/)
include_directories(model/)
include_directories(model/proxy_models)
include_directories(xmpp_services/)

add_subdirectory(model)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        widgets/LeftDrawer.cpp
        widgets/ActiveChat.cpp
        widgets/MiddleStack.cpp
        widgets/ContactListWidget.cpp
        widgets/ChatListWidget.cpp
        widgets/SettingsWidget.cpp
        xmpp_services/XmppClient.cpp
)

add_executable(Messanger ${PROJECT_SOURCES})

target_link_libraries(Messanger PRIVATE Qt6::Widgets Qt6::Network model QXmpp::QXmpp ${QXMPP_TARGET})

add_subdirectory(tests)
