cmake_minimum_required(VERSION 3.22)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    message(FATAL_ERROR "This project must only be built as a subdirectory. Configure the parent project instead.")
endif()

enable_language(ASM)

# Executable
add_executable(${CMAKE_PROJECT_NAME})

# CubeMX generated sources
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_subdirectory(cmake/stm32cubemx)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE stm32cubemx)

# Sources
set(ROBOT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Src")
file(GLOB_RECURSE ROBOT_SOURCES "${ROBOT_SOURCE_DIR}/*.cpp")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${ROBOT_SOURCES})

# Link libraries
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CORE_LIBRARY_NAME})
