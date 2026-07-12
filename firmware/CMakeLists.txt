cmake_minimum_required(VERSION 3.22)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are not allowed.")
endif()

enable_testing()

###
### Options
###

option(BUILD_FOR_HARDWARE "Build for robot hardware" OFF)
option(BUILD_FOR_DESKTOP "Build for desktop (simulation)" OFF)
option(BUILD_TESTS "Build unit tests" OFF)

# Default build for hardware
if(NOT (BUILD_FOR_HARDWARE OR BUILD_FOR_DESKTOP))
    set(BUILD_FOR_HARDWARE ON)
endif()

if(BUILD_FOR_HARDWARE AND BUILD_FOR_DESKTOP)
    message(FATAL_ERROR "Multiple build platforms selected.")
endif()

if(BUILD_TESTS AND NOT BUILD_FOR_DESKTOP)
    message(FATAL_ERROR "Unit tests can only be built for desktop.")
endif()

###
### ARM Toolchain
###

if(BUILD_FOR_HARDWARE)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/platform/robot/cmake")
    include(gcc-arm-none-eabi)
endif()

###
### Project
###

project(micromouse-firmware)

###
### Platform
###

if(BUILD_FOR_DESKTOP)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(DESKTOP_LINUX ON)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(DESKTOP_MACOS ON)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        message(FATAL_ERROR "Windows is not a supported desktop build platform, please use WSL.")
    else()
        message(FATAL_ERROR "Unsupported desktop build platform: ${CMAKE_SYSTEM_NAME}")
    endif()
endif()

###
### Languages
###

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_language(C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

###
### Build settings
###

# Default to debug build
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Export compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

###
### Core library
###

set(CORE_LIBRARY_NAME "micromouse-firmware-core")

add_library(${CORE_LIBRARY_NAME})

set(CORE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CORE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

###
### Core include directories
###

target_include_directories(${CORE_LIBRARY_NAME} PUBLIC ${CORE_INCLUDE_DIR})

###
### Core sources
###

file(GLOB_RECURSE CORE_SOURCES "${CORE_SOURCE_DIR}/*.cpp")
target_sources(${CORE_LIBRARY_NAME} PRIVATE ${CORE_SOURCES})

###
### Core compiler & Linker flags
###

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options(${CORE_LIBRARY_NAME} PUBLIC -Wall -Wextra -Werror
        # Some silly warnings are fine
        -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
    )

    # Don't optimize for debug builds
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
      target_compile_options(${CORE_LIBRARY_NAME} PRIVATE -O0)
    else()
      target_compile_options(${CORE_LIBRARY_NAME} PRIVATE -O3)
    endif()
endif()

###
### Platform targets
###

if(BUILD_TESTS)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/tests")
endif()

if(BUILD_FOR_HARDWARE)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/platform/robot")
endif()

if(BUILD_FOR_DESKTOP)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/platform/desktop")
endif()

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
