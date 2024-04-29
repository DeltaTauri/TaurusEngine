cmake_minimum_required(VERSION 3.10)

project(TaurusEngine)

list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/Platform/WinPlayer/glad/include)
list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/Platform/WinPlayer/SDL2/include)

file(GLOB SOURCES Runtime/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${PROJECT_SOURCE_DIR}/Platform/WinPlayer/glad/src/glad.c)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Platform/WinPlayer/SDL2/lib/x64/SDL2.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Platform/WinPlayer/SDL2/lib/x64/SDL2main.lib)
target_include_directories(${PROJECT_NAME} PRIVATE ${EXTRA_INCLUDES})

add_custom_command(TARGET ${PROJECT_NAME}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/Platform/WinPlayer/SDL2/lib/x64/SDL2.dll ${CMAKE_BINARY_DIR}/
    )