project(se)

set(SRC_LIST *.cpp)

add_subdirectory(src)
add_subdirectory(inc)

add_executable(se, ${SRC_LIST})