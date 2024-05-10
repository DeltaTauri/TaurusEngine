set(TARGET_NAME TaurusRuntime)

file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/External/spdlog/include)
target_link_libraries(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/External/spdlog/lib/spdlog.lib)