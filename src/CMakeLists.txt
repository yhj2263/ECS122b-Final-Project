cmake_minimum_required (VERSION 3.2) # If your CMake version is older, try modifying this line
project(ECS122B-Final-Project)

add_definitions(-std=c++11 -g)

########## Create libraries
add_library(SuffixTreeLib suffixTree.cpp createInput.cpp edge.cpp node.cpp)

########## Link GoogleTest
include_directories($ENV{GMOCK_HOME}/gtest/include)
link_directories($ENV{GMOCK_HOME}/gtest/mybuild)

########## sanity tests for suffixTree.cpp
add_executable(suffixTreeSanityTest suffixTreeSanityTest.cpp)
target_link_libraries(suffixTreeSanityTest gtest)
target_link_libraries(suffixTreeSanityTest pthread)
target_link_libraries(suffixTreeSanityTest SuffixTreeLib)

########## make the executable for main.cpp
add_executable(suffixTree main.cpp)
target_link_libraries(suffixTree SuffixTreeLib)
