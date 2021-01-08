include(CTest)
find_package(GTest)

enable_testing()

  set(SOURCES
  main.cpp
  BigNumber.cpp)

add_executable(testrunner
  "${SOURCES}")

target_compile_options(testrunner
  PRIVATE
    -Wall)

target_link_libraries(testrunner
  PRIVATE
    GTest::GTest
    library)

gtest_discover_tests(testrunner)

