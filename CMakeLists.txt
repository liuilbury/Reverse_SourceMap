cmake_minimum_required(VERSION 3.16)
project(Reverse_SourceMap)

set(CMAKE_CXX_STANDARD 14)
#头文件目录
include_directories(Project/include)
aux_source_directory(Project/src src)
#链接
add_executable(Reverse_SourceMap Project/main.cpp ${src})
#为项目引入测试功能
add_subdirectory(Test)
