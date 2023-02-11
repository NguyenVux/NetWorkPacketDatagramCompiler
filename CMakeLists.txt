cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)


set(COMMON_SOURCES)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
project("MVN Datagram Parser")
add_executable("Parser" "src/main.cpp" ${COMMON_SOURCES})
target_include_directories("Parser" PUBLIC "include")
else()
add_library(${COMMON_SOURCES})
target_include_directories("Parser" PUBLIC "include")
endif()

