cmake_minimum_required(VERSION 3.5)

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/model
        ${PROJECT_SOURCE_DIR}/tests
        ${PROJECT_SOURCE_DIR}/tests/model
        ${PROJECT_SOURCE_DIR}/tests/gui
        ${PROJECT_SOURCE_DIR}/xmpp_services
)

set(SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/mainwindow.cpp
        ${PROJECT_SOURCE_DIR}/widgets/LeftDrawer.cpp
        ${PROJECT_SOURCE_DIR}/widgets/ActiveChat.cpp
        ${PROJECT_SOURCE_DIR}/widgets/MiddleStack.cpp
        ${PROJECT_SOURCE_DIR}/widgets/ContactListWidget.cpp
        ${PROJECT_SOURCE_DIR}/widgets/ChatListWidget.cpp
        ${PROJECT_SOURCE_DIR}/widgets/SettingsWidget.cpp
        ${PROJECT_SOURCE_DIR}/widgets/AddContactWidget.cpp
        ${PROJECT_SOURCE_DIR}/model/Contact.hpp
        ${PROJECT_SOURCE_DIR}/model/Contact.cpp
        ${PROJECT_SOURCE_DIR}/model/Chat.hpp
        ${PROJECT_SOURCE_DIR}/model/Chat.cpp
        ${PROJECT_SOURCE_DIR}/tests/TestBase.cpp
        ${PROJECT_SOURCE_DIR}/tests/gui/TestGuiBase.cpp
        ${PROJECT_SOURCE_DIR}/xmpp_services/XmppClient.cpp
        ${PROJECT_SOURCE_DIR}/tests/model/TestModelBase.cpp)

set(LOCAL_LINK_LIBRARIES
        Qt6::Core
        Qt6::Gui
        Qt6::Test
        Qt6::Widgets
        Qt6::Network
        model
        ${QXMPP_TARGET}
        QXmpp::QXmpp
)

add_subdirectory(model)
add_subdirectory(gui)

enable_testing()

add_test(
  NAME TestChatListProxyModel
  COMMAND $<TARGET_FILE:TestChatListProxyModel>
)

add_test(
  NAME InitialWidgetsStatus
  COMMAND $<TARGET_FILE:InitialWidgetsStatus>
)

add_test(
  NAME ClickOnLeftDrawerButtons
  COMMAND $<TARGET_FILE:ClickOnLeftDrawerButtons> 
)

add_test(
  NAME CheckConnectionToServer
  COMMAND $<TARGET_FILE:CheckConnectionToServer>
)

add_test(
        NAME CheckConnectionToServerWithInvalidData
        COMMAND $<TARGET_FILE:CheckConnectionToServerWithInvalidData>
)

add_test(
        NAME FetchContactsFromServer
        COMMAND $<TARGET_FILE:FetchContactsFromServer>
)

add_test(
        NAME AddContact
        COMMAND $<TARGET_FILE:AddContact>
)

add_test(
  NAME StartNewChat
  COMMAND $<TARGET_FILE:StartNewChat>
)

add_test(
  NAME SelectExistingChat
  COMMAND $<TARGET_FILE:SelectExistingChat>
)

add_test(
  NAME SendNewMessageInExistingChat
  COMMAND $<TARGET_FILE:SendNewMessageInExistingChat>
)

add_test(
  NAME DeleteChat
  COMMAND $<TARGET_FILE:DeleteChat>
)