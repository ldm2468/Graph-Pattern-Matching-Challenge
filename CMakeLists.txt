cmake_minimum_required(VERSION 3.0)
project(subgraph_matching)

add_compile_options(-O3)
add_compile_options(-Wall)
add_compile_options(-std=c++11)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES src/*)

file(GLOB DATA RELATIVE ${PROJECT_SOURCE_DIR} data/*)
file(GLOB QUERY RELATIVE ${PROJECT_SOURCE_DIR} query/*)
file(GLOB CANDIDATE_SET RELATIVE ${PROJECT_SOURCE_DIR} candidate_set/*)

foreach(file ${DATA} ${QUERY} ${CANDIDATE_SET})
    configure_file("${file}" "main/${file}" COPYONLY)
endforeach()

configure_file("checker.txt" "main/checker.txt" COPYONLY)

add_subdirectory(main)
