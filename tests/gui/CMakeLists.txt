cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


include_directories(    
                    ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/model
                    ${PROJECT_SOURCE_DIR}/tests
                )

set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/mainwindow.cpp
    ${PROJECT_SOURCE_DIR}/widgets/LeftDrawer.cpp
    ${PROJECT_SOURCE_DIR}/widgets/ActiveChat.cpp
    ${PROJECT_SOURCE_DIR}/widgets/MiddleStack.cpp
    ${PROJECT_SOURCE_DIR}/widgets/ContactListWidget.cpp
    ${PROJECT_SOURCE_DIR}/widgets/ChatListWidget.cpp
    ${PROJECT_SOURCE_DIR}/widgets/SettingsWidget.cpp
    ${PROJECT_SOURCE_DIR}/model/Contact.hpp
    ${PROJECT_SOURCE_DIR}/model/Contact.cpp
    ${PROJECT_SOURCE_DIR}/model/Chat.hpp
    ${PROJECT_SOURCE_DIR}/model/Chat.cpp
    ${PROJECT_SOURCE_DIR}/tests/TestBase.cpp
    TestGuiBase.cpp)



set(LOCAL_LINK_LIBRARIES
    Qt6::Core
    Qt6::Gui
    Qt6::Test
    Qt6::Widgets
    model
)

add_executable(InitialWidgetsStatus
    InitialWidgetsStatus.cpp
    ${SOURCE_FILES}
)

target_link_libraries(InitialWidgetsStatus PRIVATE
    ${LOCAL_LINK_LIBRARIES}
)

add_executable(ClickOnLeftDrawerButtons
    ClickOnLeftDrawerButtons.cpp
    ${SOURCE_FILES}
)

target_link_libraries(ClickOnLeftDrawerButtons PRIVATE
    ${LOCAL_LINK_LIBRARIES}
)

add_executable(CheckConnectionToServer
    CheckConnectionToServer.cpp
    ${SOURCE_FILES}
    )

target_link_libraries(CheckConnectionToServer PRIVATE
    ${LOCAL_LINK_LIBRARIES}
)

add_executable(StartNewChat
    StartNewChat.cpp
    ${SOURCE_FILES}
    )

target_link_libraries(StartNewChat PRIVATE
    ${LOCAL_LINK_LIBRARIES}
)

add_executable(SelectExistingChat
    SelectExistingChat.cpp
    ${SOURCE_FILES}
    )

target_link_libraries(SelectExistingChat PRIVATE
    ${LOCAL_LINK_LIBRARIES}
)


add_executable(SendNewMessageInExistingChat
    SendNewMessageInExistingChat.cpp
    ${SOURCE_FILES}
)

target_link_libraries(SendNewMessageInExistingChat PRIVATE
    ${LOCAL_LINK_LIBRARIES}
)

add_executable(DeleteChat
    DeleteChat.cpp
    ${SOURCE_FILES}
)

target_link_libraries(DeleteChat PRIVATE
    ${LOCAL_LINK_LIBRARIES}
)
