cmake_minimum_required(VERSION 3.8)
project(Project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Automate.cpp Automate.h Transition.cpp Transition.h)
add_executable(Project ${SOURCE_FILES})