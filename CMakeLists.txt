cmake_minimum_required(VERSION 3.16)
project(CelReader LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)


add_executable(celreader celreader.cpp)

target_include_directories(celreader PUBLIC include/)
