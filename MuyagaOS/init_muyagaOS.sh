#!/usr/bin/env bash
# -------------------------------------------------------------------
# MuyagaOS Repository Initializer
# Creates full directory tree + placeholder files for VM + OS + FS
# -------------------------------------------------------------------

set -e
echo "📂 Initializing MuyagaOS repository..."

# === Top-level ===
mkdir -p vm/{include,src,devices,tests}
mkdir -p os/{include,src,fs,tests}
mkdir -p disk tools docs scripts build

# === Root files ===
cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.16)
project(MuyagaOS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vm)
add_subdirectory(os)
EOF

cat > README.md <<'EOF'
# MuyagaOS

**MuyagaOS** is a lightweight educational operating system and virtual machine written in modern C++.  
It provides a simulated 6502-like environment with a kernel, virtual file system (BJFS), and basic shell.

## Structure

- `vm/` — 6502-style CPU, memory, and I/O device emulation  
- `os/` — kernel, syscalls, and basic BJFS filesystem  
- `disk/` — virtual disk images and filesystem tools  
- `tools/` — utilities to interact with BJFS from the host  
- `docs/` — architecture and design notes  
- `scripts/` — build and run helpers  

Run `./scripts/build_all.sh` then `./scripts/run_vm.sh` to boot the VM.
EOF

# === VM ===
cat > vm/CMakeLists.txt <<'EOF'
add_library(vm STATIC
    src/cpu.cpp
    src/memory.cpp
    src/loader.cpp
    devices/console.cpp
    devices/disk.cpp
)
target_include_directories(vm PUBLIC include)
EOF

touch vm/include/{cpu.hpp,memory.hpp,devices.hpp,vm_config.hpp,instructions.hpp}
touch vm/src/{cpu.cpp,memory.cpp,loader.cpp,main_vm.cpp}
touch vm/devices/{console.cpp,disk.cpp}
touch vm/tests/{test_cpu.cpp,test_memory.cpp}

# === OS ===
cat > os/CMakeLists.txt <<'EOF'
add_library(os STATIC
    src/kernel.cpp
    src/syscalls.cpp
    src/memory_manager.cpp
    fs/bjfs.cpp
)
target_include_directories(os PUBLIC include)
target_link_libraries(os vm)
EOF

touch os/include/{kernel.hpp,syscalls.hpp,loader.hpp,fs.hpp,bjfs.hpp,memory_manager.hpp,shell.hpp}
touch os/src/{kernel.cpp,syscalls.cpp,loader.cpp,memory_manager.cpp,shell.cpp}
touch os/fs/{bjfs.cpp,bitmap.cpp}
touch os/tests/{test_fs.cpp,test_syscalls.cpp}

# === Disk and Tools ===
touch disk/disk.img
touch tools/{bjfs-ls.cpp,bjfs-cp.cpp,CMakeLists.txt}

# === Docs ===
touch docs/{architecture.md,bjfs_spec.md,syscall_table.md,boot_sequence.md,memory_map.md}

# === Scripts ===
cat > scripts/build_all.sh <<'EOF'
#!/usr/bin/env bash
set -e
mkdir -p build && cd build
cmake ..
make -j$(nproc)
EOF
chmod +x scripts/build_all.sh

cat > scripts/run_vm.sh <<'EOF'
#!/usr/bin/env bash
set -e
./build/vm/main_vm
EOF
chmod +x scripts/run_vm.sh

cat > scripts/make_disk.sh <<'EOF'
#!/usr/bin/env bash
set -e
echo "Creating new BJFS disk image..."
dd if=/dev/zero of=disk/disk.img bs=512 count=128
EOF
chmod +x scripts/make_disk.sh

echo " MuyagaOS base structure created successfully!"
