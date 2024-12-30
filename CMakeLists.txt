cmake_minimum_required(VERSION 3.15)

# Project definition
project(TekstoNuskaitymas VERSION 1.0 LANGUAGES CXX)

# Include directories
include_directories("C:/Users/vlue1/Desktop/egzaminouzd/include")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source files
file(GLOB SOURCES "C:/Users/vlue1/Desktop/egzaminouzd/src/*.cpp")

# Main executable
add_executable(TekstoNuskaitymas ${SOURCES})
