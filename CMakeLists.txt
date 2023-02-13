cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)


project("MVN Datagram Parser")
set(EXCUTABLE_TARGET "Compile")

option(RELEASE_MODE "Option description" OFF)

if(RELEASE_MODE)
  add_definitions(-D__RELEASE__)
endif()

add_definitions(-D_HAS_EXCEPTIONS=0)
include("Sources.cmake")
add_executable(${EXCUTABLE_TARGET} 
${SOURCES}
)

target_include_directories(${EXCUTABLE_TARGET} PUBLIC "include")