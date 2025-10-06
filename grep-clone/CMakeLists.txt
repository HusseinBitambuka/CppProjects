cmake_minimum_required(VERSION 3.10)

project(GREP-CLONE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output executables into top-level build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Library target (regex engine)
add_library(regex_engine
    src/parser.cpp
    src/nfa.cpp
    src/dfa.cpp
    src/matcher.cpp
    src/utils.cpp 
)

target_include_directories(regex_engine PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# CLI target
add_executable(grep_clone src/main.cpp)
target_link_libraries(grep_clone PRIVATE regex_engine)
