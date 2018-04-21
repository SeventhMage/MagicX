cmake_minimum_required (VERSION 3.3)
project (MagicX4.0)

set (MX_VERSION_MAJOR 1)
set (MX_VERSION_MINOR 0)

configure_file (
  "${PROJECT_SOURCE_DIR}/source/mxConfig.h.in"
  "${PROJECT_SOURCE_DIR}/include/mxConfig.h"
)

include_directories("${PROJECT_SOURCE_DIR}/include")

option (USE_DEVICE_WIN "use windows device" YES)

if (USE_DEVICE_WIN)
	add_subdirectory(source/devicewin)
	set (EXTRA_LIBS ${EXTRA_LIBS} devicewin)
endif (USE_DEVICE_WIN)

list(APPEND HEADER_FILES "${PROJECT_SOURCE_DIR}/include")
list(APPEND SOURCE_FILES "${PROJECT_SOURCE_DIR}/source")

add_executable(mx ${HEADER_FILES} ${SOURCE_FILES})
#add_library(mx SHARED ${PROJECT_SOURCE_DIR}/source/CMagicX.cpp ${PROJECT_SOURCE_DIR}/source/CMXDriver.cpp)
target_link_libraries(mx ${EXTRA_LIBS})

set_target_properties(mx PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

#install (TARGETS mx DESTINATION bin)
#install (FILES "${PROJECT_BINARY_DIR/mxConfig.h}" DESTINATION include)
