cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(TestChatListProxyModel
                TestChatListProxyModel.cpp
                ${SOURCE_FILES}
                )

target_link_libraries(TestChatListProxyModel PRIVATE
    ${LOCAL_LINK_LIBRARIES}
)
