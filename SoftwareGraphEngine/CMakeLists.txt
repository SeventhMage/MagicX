cmake_minimum_required(VERSION 2.8)

#project name
PROJECT(SGE)

#head file path
INCLUDE_DIRECTORIES(inc DIR_INC)

#source directory
AUX_SOURCE_DIRECTORY(src DIR_SRCS)


#set environment variable
#SET(SGE_SRC ${DIR_SRCS})

#set extern libraries
#SET(LIBRARIES libm.so)

file(GLOB_RECURSE DIR_INC  *.h *.hpp)

source_group("inc" FILES ${DIR_INC})
source_group("src" FILES ${DIR_SRCS})

#add executable file
ADD_EXECUTABLE(Engine ${DIR_SRCS} ${DIR_INC})

SET(EXECUTABLE_OUTPUT_PATH ../bin)
SET(LIBRARY_OUTPUT_PATH lib)
#add link library
#TARGET_LINK_LIBRARIES(../bin/bin ${LIBRARIES})

