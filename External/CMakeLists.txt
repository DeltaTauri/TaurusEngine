set(third_party_folder "External")

if(NOT TARGET SDL3::SDL3)
	add_subdirectory(SDL SDLBinary EXCLUDE_FROM_ALL)
	#set_target_properties(SDL3::SDL3 PROPERTIES FOLDER ${third_party_folder}/SDL)
endif()

if(NOT TARGET spdlog)
	option(SPDLOG_BUILD_EXAMPLE "" OFF)
	option(SPDLOG_INSTALL "" OFF)
	add_subdirectory(spdlog spdlogLibrary)
	set_target_properties(spdlog PROPERTIES FOLDER ${third_party_folder}/spdlog)
endif()

if(NOT TARGET glm)
	add_subdirectory(glm glmLibrary)
endif()