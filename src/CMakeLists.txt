cmake_minimum_required (VERSION 3.2) # If your CMake version is older, try modifying this line
project(ECS122B-Final-Project)

add_definitions(-std=c++1z -g)

########## Create libraries
add_library(SuffixTreeLib suffixTree.cpp)

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

########## make the executable for longestCommonSubstr.cpp
add_executable(longestCommonSubstr LongestCommonSubstr.cpp)
target_link_libraries(longestCommonSubstr SuffixTreeLib)

########## make the test executable for generalized suffixTree
add_executable(longestCommonSubstrTests longestCommonSubstrTests.cpp)
target_link_libraries(longestCommonSubstrTests SuffixTreeLib)
target_link_libraries(longestCommonSubstrTests gtest)
target_link_libraries(longestCommonSubstrTests pthread)
add_custom_command(TARGET longestCommonSubstrTests
                   POST_BUILD
                   COMMAND longestCommonSubstrTests
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   COMMENT "Running longestCommonSubstrTests" VERBATIM)

########## make the sanity test executable for LongestCommonSubstring
add_executable(longestCommonSubstrSanityTest longestCommonSubstrSanityTest.cpp)
target_link_libraries(longestCommonSubstrSanityTest SuffixTreeLib)
target_link_libraries(longestCommonSubstrSanityTest gtest)
target_link_libraries(longestCommonSubstrSanityTest pthread)

########## make the executable for maximalRepeats.cpp
add_executable(maximalRepeats maximalRepeats.cpp)
target_link_libraries(maximalRepeats SuffixTreeLib)

########## make the executable for circular string linearization
add_executable(circStrLinearization circStrLinearization.cpp)
target_link_libraries(circStrLinearization SuffixTreeLib)
