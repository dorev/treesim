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

set(GLM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tmp/glm")
include(ExternalProject)
ExternalProject_Add(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    PREFIX ${GLM_DIR}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)
ExternalProject_Get_Property(glm source_dir)
set(GLM_INCLUDE_DIR ${source_dir}/glm)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIR})
add_dependencies(${PROJECT_NAME} glm)
