cmake_minimum_required(VERSION 3.7)
project(ow_riscv_emu)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(riscvLib)
add_subdirectory(riscvTest)
add_executable( riscvElfEmu main.cpp)
add_dependencies( riscvElfEmu riscvLib )
target_link_libraries(riscvElfEmu riscvLib)

add_test(test_all riscvTest)
