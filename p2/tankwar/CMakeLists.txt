cmake_minimum_required(VERSION 3.10.2)
project(hw8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(layer3 layer3.cpp layer1.h layer2.h)
