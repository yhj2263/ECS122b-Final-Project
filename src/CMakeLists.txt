cmake_minimum_required (VERSION 3.2) # If your CMake version is older, try modifying this line
project(ECS122B-Final-Project)

add_definitions(-std=c++11 -g)

########## Create libraries
add_library(SuffixTreeLib suffixTree.cpp createInput.cpp edge.cpp node.cpp)

########## Link GoogleTest
include_directories($ENV{GMOCK_HOME}/gtest/include)
link_directories($ENV{GMOCK_HOME}/gtest/mybuild)

########## unit tests for suffixTree.cpp
add_executable(suffixTreeTests suffixTreeTests.cpp)
target_link_libraries(suffixTreeTests gtest)
target_link_libraries(suffixTreeTests pthread)
target_link_libraries(suffixTreeTests SuffixTreeLib)
add_custom_command(TARGET suffixTreeTests
                   POST_BUILD
                   COMMAND suffixTreeTests
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   COMMENT "Running suffixTreeTests" VERBATIM)

########## make the executable for main.cpp
add_executable(suffixTree main.cpp)
target_link_libraries(suffixTree SuffixTreeLib)
