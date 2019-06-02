set(SOURCES_PROG
  main.cpp)

add_executable(program
  ${SOURCES_PROG})

target_compile_options(program
  PRIVATE
    -Wall
    -Werror)

target_link_libraries(program
  PRIVATE
    library)
