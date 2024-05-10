set(TARGET_NAME TaurusEditor)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(SDL2_ROOT_DIR "${PROJECT_SOURCE_DIR}/External/SDL2")
find_package(SDL2 REQUIRED)
list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/External/SDL2/include)
list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/External/glad/include)
list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/Engine/Source/Runtime/Core/Log)

file(GLOB EDITOR_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${TARGET_NAME} ${EDITOR_SOURCES} ${PROJECT_SOURCE_DIR}/External/glad/src/glad.c)

target_link_libraries(${TARGET_NAME} PRIVATE ${OPENGL_gl_LIBRARY} SDL2::SDL2main TaurusRuntime)
target_include_directories(${TARGET_NAME} PRIVATE ${EXTRA_INCLUDES} )

add_custom_command(TARGET ${TARGET_NAME}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_RUNTIME_LIBRARY}" ${CMAKE_BINARY_DIR}/Engine/Source/Editor
    )