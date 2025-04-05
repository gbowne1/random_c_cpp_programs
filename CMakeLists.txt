cmake_minimum_required(VERSION 3.10)

# Project name
project(MyProject)

# Specify the output directory for build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Define source directories
set(C_SOURCE_DIR ${CMAKE_SOURCE_DIR}/c_programs)
set(CPP_SOURCE_DIR ${CMAKE_SOURCE_DIR}/cpp_programs)

# Find all C and C++ source files
file(GLOB C_SOURCES "${C_SOURCE_DIR}/*.c")
file(GLOB CPP_SOURCES "${CPP_SOURCE_DIR}/*.cpp")

# Add executable
add_executable(${PROJECT_NAME} ${C_SOURCES} ${CPP_SOURCES})

# Set C++ standard
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

# Link the math library for C files
if(UNIX) # macOS and Linux
    target_link_libraries(${PROJECT_NAME} m)
elseif(WIN32) # Windows
    target_link_libraries(${PROJECT_NAME} "") # Math functions are generally part of MSVC runtime
endif()
