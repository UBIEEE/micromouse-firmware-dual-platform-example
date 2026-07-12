cmake_minimum_required(VERSION 3.22)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    message(FATAL_ERROR "This project must only be built as a subdirectory. Configure the parent project instead.")
endif()

enable_testing()

project(micromouse-firmware-tests)

# Get GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        6910c9d
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# Executable
add_executable(${PROJECT_NAME})

# Sources
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${TEST_SOURCES})

# Link to core library
target_link_libraries(${PROJECT_NAME} ${CORE_LIBRARY_NAME})

# Link to Google Test
target_link_libraries(${PROJECT_NAME} GTest::gtest_main GTest::gmock)

gtest_discover_tests(${PROJECT_NAME})
