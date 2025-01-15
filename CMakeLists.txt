cmake_minimum_required(VERSION 3.15...3.31)

project(
  MindYourBusiness
  VERSION 0.1
  DESCRIPTION "An example project with CMake"
  LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES *.cpp *.h)

add_executable(MindYourBusiness ${SOURCES})