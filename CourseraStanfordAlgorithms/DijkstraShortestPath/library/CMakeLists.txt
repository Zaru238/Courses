set(TARGET library)

set(SOURCES
  foo.cpp)

add_library(${TARGET} STATIC
  ${SOURCES})

target_compile_options(${TARGET}
  PRIVATE
    -Wall
    -Werror)

  target_include_directories(${TARGET}
  INTERFACE
    include
  PRIVATE
    include/${TARGET})

add_custom_command(TARGET ${TARGET} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR})

