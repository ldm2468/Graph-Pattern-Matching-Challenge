add_executable(program main.cc ${SOURCES})

add_executable(program_debug main.cc ${SOURCES})
target_compile_definitions(program_debug PRIVATE VERIFY_EMBEDDINGS)

add_executable(check check.cc ${SOURCES})
add_dependencies(check program)
