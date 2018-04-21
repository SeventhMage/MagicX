file(GLOB_RECURSE HEADER_FILES *.h *.inl)
file (GLOB_RECURSE SOURCE_FILES *.cpp *.cc *.c)
add_library(devicewin ${HEADER_FILES} ${SOURCE_FILES})

#install (TARGETS devicewin DESTINATION bin)
#install (FILES CDeviceWin.h DESTINATION include)