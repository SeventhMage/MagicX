add_subdirectory(base)
add_subdirectory(glrender)
add_subdirectory(resource)
add_subdirectory(scene)

if (MX_BUILD_PLATFORM_WINDOWS)
	add_subdirectory(devicewin)
endif (MX_BUILD_PLATFORM_WINDOWS)