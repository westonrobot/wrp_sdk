cmake_minimum_required(VERSION 3.10.2)
project(wrp_sdk_sample)

## Set compiler to use c++ 14 features
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Add additional path for CMake to find wrp_sdk (IMPORTANT)
list(APPEND CMAKE_PREFIX_PATH "/opt/weston_robot/lib/cmake")

## Use GNUInstallDirs to install libraries into correct locations on all platforms.
include(GNUInstallDirs)

## Put all binary files into /bin and libraries into /lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

## Find wrp_sdk and its dependent package wrp_zbus
find_package(wrp_sdk 1.3.0...<1.4.0 REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LelyIO QUIET IMPORTED_TARGET liblely-io2)
pkg_check_modules(LelyCOAPP QUIET IMPORTED_TARGET liblely-coapp)

set(BUILD_PERIPH_MODULE OFF)
if(LelyIO_FOUND AND LelyCOAPP_FOUND)
    message(STATUS "Lely-core libraries found, peripheral module will be included")
    set(BUILD_PERIPH_MODULE ON)
endif()

## Add your target
add_subdirectory(sample)