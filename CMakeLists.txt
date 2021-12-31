cmake_minimum_required(VERSION 2.8.3)
project(robot_base)

## Set compiler to use c++ 11 features
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Add additional path for CMake to find wrp_sdk (IMPORTANT)
list(APPEND CMAKE_PREFIX_PATH "/opt/weston_robot/lib/cmake")

## Find wrp_sdk and its dependent package wrp_zbus
find_package(wrp_sdk REQUIRED)
find_package(wrp_zbus REQUIRED)

## Add your target
add_executable(sdk_demo src/sdk_demo.cpp)
target_link_libraries(sdk_demo PRIVATE westonrobot::wrp_sdk)
