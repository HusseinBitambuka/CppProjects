add_library(os STATIC
    src/kernel.cpp
    src/syscalls.cpp
    src/memory_manager.cpp
    fs/bjfs.cpp
)
target_include_directories(os PUBLIC include)
target_link_libraries(os vm)
