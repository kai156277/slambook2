cmake_minimum_required(VERSION 3.5)

project(hello_slam)

# set(VERSION 1.0)

## ------------------------------------------------------------------------- ##
## create libhello_slam.a
add_library(hello_slam STATIC 
    src/libHelloSLAM.cpp
)

target_include_directories(hello_slam
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

## ------------------------------------------------------------------------- ##
## install libhello_slam

# binaries
# install(TARGETS hello_slam DESTINATION bin)

# library
install(TARGETS hello_slam LIBRARY DESTINATION lib)

# header files
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

## ------------------------------------------------------------------------- ##
# set hello_slam cmake module path

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
message("cmake_module_path: ${CMAKE_MODULE_PATH}")
find_package(hello_slam 1.0 REQUIRED)

if(LIBHELLO_SLAM_FOUND)
    message("hello_slam lib v1.0 found")
else()
    message(FATAL_ERROR "hello_slam lib v1.0 found")
endif()

## ------------------------------------------------------------------------- ##
## create hello_slam_bin
add_executable(hello_slam_bin useHello.cpp)

target_link_libraries(hello_slam_bin PRIVATE hello_slam)
## ------------------------------------------------------------------------- ##