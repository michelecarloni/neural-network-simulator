cmake_minimum_required(VERSION 3.31.2)
project(NeuralNetworkInCpp)

#Include headers 
include_directories(header)

#Include all c++ files
file(GLOB SOURCES source/*.cpp)

add_executable(main main.cpp ${SOURCES})