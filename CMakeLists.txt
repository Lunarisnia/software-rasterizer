cmake_minimum_required(VERSION 3.24)

project(software_rasterizer
    VERSION 0.1.0
    DESCRIPTION "A software rasterizer written in C++"
    LANGUAGES CXX
)

include(GNUInstallDirs)

option(SWR_BUILD_TESTS "Build tests" ON)
option(SWR_BUILD_EXAMPLES "Build examples" ON)
option(SWR_ENABLE_WARNINGS "Enable compiler warnings" ON)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/CompilerWarnings.cmake)
include(cmake/Dependencies.cmake)

add_subdirectory(src)

if(SWR_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(SWR_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
