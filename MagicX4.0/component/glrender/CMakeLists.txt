file(GLOB_RECURSE HEADER_FILES *.h *.inl)
file (GLOB_RECURSE SOURCE_FILES *.cpp *.cc *.c)
set(ALL_FILES ${HEADER_FILES} ${SOURCE_FILES})
add_library(glrender ${ALL_FILES})

set_target_properties(glrender PROPERTIES FOLDER "Component")