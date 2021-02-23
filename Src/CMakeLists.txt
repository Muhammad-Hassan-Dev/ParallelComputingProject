cmake_minimum_required(VERSION 2.8.12)

#Set Project Name
project(ParallelComputingProject)

#Specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Add Executable
add_executable(Main.out Main.cpp)

#Resolve <pthreads> Inclusion
target_link_libraries(Main.out pthread)
