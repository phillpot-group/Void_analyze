file(GLOB_RECURSE SRC "*.cpp")
add_library(settings settings.cpp)
add_executable(void_analyze ${SRC})
