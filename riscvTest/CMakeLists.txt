cmake_minimum_required(VERSION 3.7)
project(ow_riscv_emu)
enable_testing()

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

add_subdirectory(riscv-elf)

add_executable( riscvTest main_test.cpp test_alu.cpp test_basics.cpp test_load.cpp test_store.cpp test_branch.cpp test_jump.cpp test_utype.cpp RiscCpuBaseTest.h test_integration.cpp)
add_dependencies( riscvTest riscvLib )
add_dependencies(riscvTest gtest)
add_dependencies(riscvTest risc-native-test)
target_link_libraries(riscvTest gtest)
target_link_libraries(riscvTest riscvLib)

add_test(test_me riscvTest)