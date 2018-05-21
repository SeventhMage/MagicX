cmake_minimum_required (VERSION 3.3)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS On)

project (MagicX4.0)

set (MX_VERSION_MAJOR 1)
set (MX_VERSION_MINOR 0)

configure_file (
  "${PROJECT_SOURCE_DIR}/source/mxConfig.h.in"
  "${PROJECT_SOURCE_DIR}/include/mxConfig.h"
)

#add_definitions(-D__cplusplus)

if(WIN32)
	option(MX_BUILD_PLATFORM_WINDOWS "" TRUE)
	option(MX_BUILD_PLATFORM_ANDROID "" FALSE)
	option(MX_BUILD_PLATFORM_IOS "" FALSE)
elseif(APPLE)
	set(CMAKE_C_COMPILER g++)
	set(CMAKE_CXX_COMPILER g++)
	option(MX_BUILD_PLATFORM_WINDOWS "" FALSE)
	option(MX_BUILD_PLATFORM_ANDROID "" FALSE)
	option(MX_BUILD_PLATFORM_IOS "" TRUE)
else()
	option(MX_BUILD_PLATFORM_WINDOWS "" FALSE)
	option(MX_BUILD_PLATFORM_ANDROID "" TRUE)
	option(MX_BUILD_PLATFORM_IOS "" FALSE)
endif()

if(WIN32)
	option(MX_RENDERER_OPENGL "" TRUE)
	option(MX_RENDERER_OPENGLES "" FALSE)
	option(MX_RENDERER_SOFTWARE "" FALSE)
else()
	option(MX_RENDERER_OPENGL "" FALSE)
	option(MX_RENDERER_OPENGLES "" TRUE)
	option(MX_RENDERER_SOFTWARE "" FALSE)
endif()

#输出文件路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
if (MX_BUILD_PLATFORM_IOS)
	set(CMAKE_LIBRARY_OUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
	set(CMAKE_ARCHIVE_OUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
else()
	set(CMAKE_LIBRARY_OUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}")
	set(LIBRARY_OUTPUT_PATH ${CMAKE_LIBRARY_OUT_DIRECTORY})
	set(CMAKE_ARCHIVE_OUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}")
endif()

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/component")


file(GLOB_RECURSE HEADER_FILES include/*.h)
file(GLOB_RECURSE SOURCE_FILES source/*.cpp)
set(ALL_FILES ${HEADER_FILES} ${SOURCE_FILES})


macro(source_group_by_dir source_files)
    #if(MSVC)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(sgbd_file ${${source_files}})
            string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif(sgbd_nogroup)
            source_group(${sgbd_group_name} FILES ${sgbd_file})
        endforeach(sgbd_file)
    #endif(MSVC)
endmacro(source_group_by_dir)

source_group_by_dir(ALL_FILES) 

add_subdirectory(component)

aux_source_directory(./source SRC_LIST)

file(GLOB_RECURSE INC ${PROJECT_SOURCE_DIR}/include/*.h)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})
add_library(mx ${ALL_FILES})

if(WIN32)
	set(DEVICE_LIB devicewin)
endif()

if(MX_RENDERER_OPENGL)
	set(RENDER_LIB glrender)
elseif(MX_RENDERER_OPENGLES)
	set(RENDER_LIB glesrender)
else()
	set(RENDER_LIB softrender)
endif()

target_link_libraries(mx base ${DEVICE_LIB} ${RENDER_LIB} resource scene opengl32 glew32)

set_target_properties(mx PROPERTIES FOLDER "MagicX")

add_subdirectory(example/1.triangle)