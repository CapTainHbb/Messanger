cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(HandleTwoRostersContacts
        HandleTwoRostersContacts.cpp
        ${SOURCE_FILES}
)

target_link_libraries(HandleTwoRostersContacts PRIVATE
        ${LOCAL_LINK_LIBRARIES}
)
