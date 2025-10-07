add_library(vm STATIC
    src/cpu.cpp
    src/memory.cpp
    src/loader.cpp
    devices/console.cpp
    devices/disk.cpp
)
target_include_directories(vm PUBLIC include)
