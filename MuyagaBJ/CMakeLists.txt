cmake_minimum_required(VERSION 3.16)
project(MuyagaBJ LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})



include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

add_executable(muyagabj ${SRC_FILES})
