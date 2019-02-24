cmake_minimum_required(VERSION 3.13)
project(Template LANGUAGES CXX)

set (CMAKE_C_COMPILER "clang")
set (CMAKE_CXX_COMPILER "clang++")
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

#Cppcheck setup
find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
if (CMAKE_CXX_CPPCHECK)
  list(APPEND CMAKE_CXX_CPPCHECK
    "--enable=warning"
    "--inconclusive"
    "--force"
  )
endif()

include(CTest)
find_package(GTest)

enable_testing()

set(SOURCES
  src/BigNumber.cpp
)

set(TEST_SOURCES
  test/main.cpp
  test/BigNumber.cpp
)


add_executable(testrunner
  "${SOURCES}"
  "${TEST_SOURCES}")

target_compile_options(testrunner
  PRIVATE
    -Wall
    -Werror)

target_include_directories(testrunner
  PRIVATE
    src
    test)

target_link_libraries(testrunner
  PRIVATE
    GTest::GTest)

gtest_discover_tests(testrunner)
