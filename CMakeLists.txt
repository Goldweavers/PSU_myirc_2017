cmake_minimum_required(VERSION 3.6)
project(PSU_myirc_2017)

set(CMAKE_C_STANDARD 11)
include_directories("includes")
file(GLOB_RECURSE SOURCE_FILES "sources/*.c" "includes/*.h")
add_executable(PSU_myirc_2017 ${SOURCE_FILES})