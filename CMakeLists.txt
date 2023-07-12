cmake_minimum_required(VERSION 3.22)
project(WMB)
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE DEMO "demo/helloworld.cpp")

add_library(Bitmap STATIC bitmap/bitmap.cpp bitmap/bitmap.h)
add_subdirectory(glm)


#src files
add_executable(WMB ${SOURCES} ${DEMO})
target_link_libraries(WMB glm)
target_link_libraries(WMB Bitmap)

#headers