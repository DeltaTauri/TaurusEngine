cmake_minimum_required(VERSION 3.10)

project(TaurusEngine)

list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/Platform/WinPlayer/glad/include)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(SDL2_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Platform/WinPlayer/SDL2")
find_package(SDL2 REQUIRED)
list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/Platform/WinPlayer/SDL2/include)

file(GLOB SOURCES Runtime/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${PROJECT_SOURCE_DIR}/Platform/WinPlayer/glad/src/glad.c)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_gl_LIBRARY} SDL2::SDL2main)
target_include_directories(${PROJECT_NAME} PRIVATE ${EXTRA_INCLUDES})

add_custom_command(TARGET ${PROJECT_NAME}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_RUNTIME_LIBRARY}" ${CMAKE_BINARY_DIR}/
    )