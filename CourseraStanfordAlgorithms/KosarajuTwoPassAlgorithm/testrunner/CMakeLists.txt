include(CTest)
find_package(GTest)

enable_testing()

set(TARGET testrunner)

set(SOURCES
  main.cpp
  foo.cpp)

add_executable(${TARGET}
  "${SOURCES}")

target_compile_options(${TARGET}
  PRIVATE
    -Wall
    -Werror)

target_link_libraries(${TARGET}
  PRIVATE
    GTest::GTest
    library)

gtest_discover_tests(${TARGET})

