set(SOURCES
  BigNumber.cpp)

add_library(library STATIC
  ${SOURCES})

target_compile_options(library
  PRIVATE
    -Wall)

target_include_directories(library
  INTERFACE
    include
  PRIVATE
    include/library)
