cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(TreeSim LANGUAGES CXX)
set(SOURCES_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE
    SOURCES
    ${SOURCES_ROOT}/*.c
    ${SOURCES_ROOT}/*.cpp
    ${SOURCES_ROOT}/*.cxx
    ${SOURCES_ROOT}/*.h
    ${SOURCES_ROOT}/*.hpp
)
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME}
    PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
