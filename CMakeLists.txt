cmake_minimum_required(VERSION 3.5)

project(Messanger VERSION 0.1 LANGUAGES CXX)

include(CTest)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Test)

include_directories(widgets/)

add_subdirectory(model)

include_directories(model/)
include_directories(model/proxy_models)

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
)

add_executable(Messanger ${PROJECT_SOURCES})

target_link_libraries(Messanger PRIVATE Qt6::Widgets model)

add_subdirectory(tests)
