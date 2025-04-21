set(TARGET_NAME TaurusRuntime)

list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/External/glad/include)
list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/Engine/Source/Runtime)

file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${TARGET_NAME} PRIVATE ${OPENGL_gl_LIBRARY} SDL3::SDL3)
target_link_libraries(${TARGET_NAME} PUBLIC spdlog::spdlog)
target_link_libraries(${TARGET_NAME} PUBLIC glm::glm)

target_include_directories(${TARGET_NAME} PRIVATE ${EXTRA_INCLUDES})
