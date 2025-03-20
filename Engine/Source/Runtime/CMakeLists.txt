set(TARGET_NAME TaurusRuntime)

add_subdirectory(${PROJECT_SOURCE_DIR}/External/SDL SDLBinary EXCLUDE_FROM_ALL)
add_subdirectory(${PROJECT_SOURCE_DIR}/External/spdlog spdlogLibrary )

list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/External/glad/include)
list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/Engine/Source/Runtime)

file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${TARGET_NAME} PRIVATE ${OPENGL_gl_LIBRARY} SDL3::SDL3)
target_link_libraries(${TARGET_NAME} PUBLIC spdlog::spdlog)

target_include_directories(${TARGET_NAME} PRIVATE ${EXTRA_INCLUDES})

if (WIN32)
    add_custom_command(TARGET ${TARGET_NAME}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL3::SDL3> $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
    add_custom_command(TARGET ${TARGET_NAME}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:spdlog::spdlog> $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
endif()