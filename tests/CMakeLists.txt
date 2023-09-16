cmake_minimum_required(VERSION 3.5)

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