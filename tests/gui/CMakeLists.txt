cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

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

add_executable(CheckConnectionToServerWithInvalidData
        CheckConnectionToServerWithInvalidData.cpp
        ${SOURCE_FILES}
)

target_link_libraries(CheckConnectionToServerWithInvalidData PRIVATE
        ${LOCAL_LINK_LIBRARIES}
)

add_executable(FetchContactsFromServer
        FetchContactsFromServer.cpp
        ${SOURCE_FILES}
)

target_link_libraries(FetchContactsFromServer PRIVATE
        ${LOCAL_LINK_LIBRARIES}
)

add_executable(AddContact
        AddContact.cpp
        ${SOURCE_FILES}
)

target_link_libraries(AddContact PRIVATE
        ${LOCAL_LINK_LIBRARIES}
)

add_executable(AddContactAndStartNewChat
        AddContactAndStartNewChat.cpp
        ${SOURCE_FILES}
)

target_link_libraries(AddContactAndStartNewChat PRIVATE
        ${LOCAL_LINK_LIBRARIES}
)


add_executable(StartNewChatForExistingContact
        StartNewChatForExistingContact.cpp
    ${SOURCE_FILES}
    )

target_link_libraries(StartNewChatForExistingContact PRIVATE
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
