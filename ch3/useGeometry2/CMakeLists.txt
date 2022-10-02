cmake_minimum_required(VERSION 3.0)

project(MyGeometry)

find_package(Eigen3 REQUIRED)
# 添加Eigen头文件
# include_directories( "/usr/include/eigen3" )

find_package(fmt REQUIRED)

add_executable(MyGeometry MyGeometry.cpp)

# 不加这一行找不到头文件
target_link_libraries(MyGeometry Eigen3::Eigen fmt::fmt)