set(TARGET program)

set(SOURCES_PROG
  main.cpp)

add_executable(${TARGET}
  ${SOURCES_PROG})

target_compile_options(${TARGET}
  PRIVATE
    -Wall
    -Werror)

target_link_libraries(${TARGET}
  PRIVATE
    library)

add_custom_command(TARGET ${TARGET} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/${TARGET}/arks.txt ${PROJECT_BINARY_DIR})
