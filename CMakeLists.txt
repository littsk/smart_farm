cmake_minimum_required(VERSION 3.8)
project(sensor_collect)
set(CMAKE_BUILD_TYPE "Debug")

add_executable(sensor_collect main.cpp)

add_subdirectory(tool)

find_package(OpenCV REQUIRED)
target_link_libraries(sensor_collect PUBLIC uart log tcp libMVSDK.so ${OpenCV_LIBS})
target_include_directories(sensor_collect PUBLIC tool/include)
