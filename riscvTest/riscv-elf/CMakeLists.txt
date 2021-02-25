cmake_minimum_required(VERSION 3.7)
project(ow_riscv_emu)

enable_language(C ASM)

set(CMAKE_CROSSCOMPILING true)

set(CMAKE_SYSTEM_NAME unknown)
set(CMAKE_SYSTEM_PROCESSOR riscv32)

set(CMAKE_SYSROOT /opt/riscv/sysroot)
set(CMAKE_STAGING_PREFIX /opt/riscv)
set(tools /opt/riscv)

set(CMAKE_C_COMPILER ${tools}/bin/riscv32-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/riscv32-unknown-elf-g++)
set(CMAKE_ASM_COMPILER ${tools}/bin/riscv32-unknown-elf-gcc)

set(LINKER_SCRIPT "riscv-emu.ld")
set ( CMAKE_C_FLAGS "-ffreestanding -O0 -Wl,--gc-sections -nostartfiles -Wl,-T,${CMAKE_CURRENT_SOURCE_DIR}/${LINKER_SCRIPT} ")

set(DRIVER_SRC
    driver/SerialPortDriver.c
    driver/SerialPortDriver.h
)

set(STARTUP_SRC
    crt0.s
        )

file( GLOB TEST_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.c )
SET(TEST_NAMES "")
foreach( testsourcefile  ${TEST_SOURCES} )
    # I used a simple string replace, to cut off .cpp.
    string( REPLACE "test/" "" testnameA ${testsourcefile} )
    string( REPLACE ".c" ".rv32" testname ${testnameA} )

    add_executable( ${testname} ${testsourcefile} ${STARTUP_SRC} ${DRIVER_SRC})
    target_include_directories( ${testname} PRIVATE driver)
    LIST(APPEND TEST_NAMES  "${testname}")
    MESSAGE(${TEST_NAMES})
    # Make sure YourLib is linked to each app
endforeach( testsourcefile ${APP_SOURCES} )

ADD_CUSTOM_TARGET(risc-native-test)
ADD_DEPENDENCIES(risc-native-test ${TEST_NAMES} )
