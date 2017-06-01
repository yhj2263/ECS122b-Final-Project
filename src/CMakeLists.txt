cmake_minimum_required (VERSION 3.2) # If your CMake version is older, try modifying this line
project(ECS122B-Final-Project)

add_definitions(-std=c++1z -g)

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

########## make the executable for LongestCommonSubstr.cpp
add_executable(LongestCommonSubstr LongestCommonSubstr.cpp)
target_link_libraries(LongestCommonSubstr SuffixTreeLib)

########## make the test executable for generalized suffixTree
add_executable(GeneralizedSuffixTreeTests generalizedSuffixTreeTests.cpp)
target_link_libraries(GeneralizedSuffixTreeTests SuffixTreeLib)
target_link_libraries(GeneralizedSuffixTreeTests gtest)
target_link_libraries(GeneralizedSuffixTreeTests pthread)
add_custom_command(TARGET GeneralizedSuffixTreeTests
                   POST_BUILD
                   COMMAND GeneralizedSuffixTreeTests
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   COMMENT "Running GeneralizedSuffixTreeTests" VERBATIM)

########## make the sanity test executable for LongestCommonSubstring
add_executable(LongestCommonSubstrSanityTest longestCommonSubstrSanityTest.cpp)
target_link_libraries(LongestCommonSubstrSanityTest SuffixTreeLib)
target_link_libraries(LongestCommonSubstrSanityTest gtest)
target_link_libraries(LongestCommonSubstrSanityTest pthread)
