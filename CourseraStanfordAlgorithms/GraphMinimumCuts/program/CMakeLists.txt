set(SOURCES_PROG
  main.cpp)

add_executable(program
  ${SOURCES_PROG})

set(data_file "${CMAKE_CURRENT_SOURCE_DIR}/kargerMinCut.txt")

add_custom_command(TARGET program POST_BUILD
                   DEPENDS "${data_file}"
                   COMMAND sh -c "pwd"
                   COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:program>"
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different "${data_file}" "$<TARGET_FILE_DIR:program>")


target_compile_options(program
  PRIVATE
    -Wall
    -Werror)

target_link_libraries(program
  PRIVATE
    library
    stdc++fs)
