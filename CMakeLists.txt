# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the project name and specify the language as C
project(VIRTUAL-AUTOSAR-SOFTWARE-COMPONENT C)

# Define the name for our final executable
set(EXECUTABLE_NAME autosar_test)

# Create the executable from all the necessary source files
add_executable(${EXECUTABLE_NAME}
    main.c
    swc/src/SeatbeltReminder_SWC.c
    stubs/rte_stubs.c
)

# equivalent of the "-I" flags in gcc command.
target_include_directories(${EXECUTABLE_NAME} PUBLIC
    swc/include
    stubs
)