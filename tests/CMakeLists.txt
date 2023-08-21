cmake_minimum_required(VERSION 3.5)


include_directories(../)

add_executable(testgui testgui.cpp ../mainwindow.cpp ../widgets/LeftDrawer.cpp ../widgets/ActiveChat.cpp)

target_link_libraries(testgui PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Test
    Qt5::Widgets
)
