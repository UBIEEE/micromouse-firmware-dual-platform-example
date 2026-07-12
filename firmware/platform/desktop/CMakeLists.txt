cmake_minimum_required(VERSION 3.22)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    message(FATAL_ERROR "This project must only be built as a subdirectory. Configure the parent project instead.")
endif()

set(DESKTOP_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(DESKTOP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Executable
add_executable(${CMAKE_PROJECT_NAME})

# Includes
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${DESKTOP_INCLUDE_DIR}")

# Sources
file(GLOB_RECURSE DESKTOP_SOURCES "${DESKTOP_SOURCE_DIR}/*.cpp")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${DESKTOP_SOURCES})

# Link libraries
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CORE_LIBRARY_NAME})
