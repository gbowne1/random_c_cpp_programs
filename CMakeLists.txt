cmake_minimum_required(VERSION 3.10)
project(MyProject C CXX)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

file(GLOB C_SOURCES "c_programs/*.c")
file(GLOB CPP_SOURCES "cpp_programs/*.cpp")

# List of C files requiring -lm
set(MATH_FILES
    barycentric cintegral complexquadr complexvector distprime eigenvalue euclidianvector
    fingerclient fingerserver gageblockstack invmatrix kirchoffs lowpassfil quadraditsolv
    rcnetwork resistance resistorcolor sqrtnewton stddeviation
)

foreach(cfile ${C_SOURCES})
    get_filename_component(fname ${cfile} NAME_WE)
    add_executable(${fname} ${cfile})

    if(${fname} IN_LIST MATH_FILES)
        target_link_libraries(${fname} m)
    endif()

    if(${fname} STREQUAL "fingerclient" OR ${fname} STREQUAL "fingerserver")
        if(WIN32)
            target_link_libraries(${fname} ws2_32)
        endif()
    endif()

    set_target_properties(${fname} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endforeach()

foreach(cppfile ${CPP_SOURCES})
    get_filename_component(fname ${cppfile} NAME_WE)
    add_executable(${fname} ${cppfile})
    set_target_properties(${fname} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endforeach()

# Enable verbose output for debugging and development
set(CMAKE_VERBOSE_MAKEFILE ON)

