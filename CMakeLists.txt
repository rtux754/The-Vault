cmake_minimum_required(VERSION 3.10)

# Nama projek
project(TheVault)

# Gunakan standar C++ modern
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tambahkan file sumber
add_executable(TheVault main.cpp metadata_manager.cpp) 

# Jika nanti ada folder include khusus
# target_include_directories(TheVault PUBLIC include)
