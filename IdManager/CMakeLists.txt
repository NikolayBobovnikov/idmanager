# CMakeList.txt : CMake project for IdManager, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("SequenceId")
add_subdirectory (src) 
add_subdirectory (test)
enable_testing ()
