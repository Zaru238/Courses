set(SOURCES
  foo.cpp)

add_library(library STATIC
  ${SOURCES})

target_compile_options(library
  PRIVATE
    -Wall
    -Werror)

target_link_libraries(library
  PRIVATE
    pthread)

target_include_directories(library
  INTERFACE
    include
  PRIVATE
    include/library)
