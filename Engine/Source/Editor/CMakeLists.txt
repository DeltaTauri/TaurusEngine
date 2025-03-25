set(TARGET_NAME TaurusEditor)


list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/External/glad/include)
list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/Engine/Source/Runtime)

file(GLOB EDITOR_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${TARGET_NAME} ${EDITOR_SOURCES} ${PROJECT_SOURCE_DIR}/External/glad/src/glad.c)

target_link_libraries(${TARGET_NAME} PRIVATE TaurusRuntime)

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
    add_custom_command(TARGET ${TARGET_NAME}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:imgui> $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
endif()