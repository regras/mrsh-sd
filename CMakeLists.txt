cmake_minimum_required(VERSION 3.5)

#set(CMAKE_VERBOSE_MAKEFILE off)

project(mrsh_sd)

set(CMAKE_CXX_FLAGS "-w -std=c++14 -ggdb -O3 -D_BSD_SOURCE -fpermissive")

set(CPP_FILES
    src/sdhash.cpp
    src/bloomfilter.cpp
    src/hashing.cpp
    src/helper.cpp
    src/main.cpp)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

include(FindBoost)
find_package(Boost 1.73.0 EXACT REQUIRED COMPONENTS filesystem)
set_source_files_properties(${CPP_FILES} PROPERTIES LANGUAGE CXX)


add_executable(mrsh_sd  ${CPP_FILES})

target_link_libraries(mrsh_sd -lm -lssl -lcrypto -lsqlite3 Boost::filesystem)
