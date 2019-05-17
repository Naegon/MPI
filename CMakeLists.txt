cmake_minimum_required(VERSION 3.8)
project(Project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES E4-main.cpp E4-Automate.cpp E4-Automate.h E4-Transition.cpp E4-Transition.h E4-fonction.cpp E4-fonction.h E4-processus.cpp E4-processus.h)
add_executable(Project ${SOURCE_FILES})