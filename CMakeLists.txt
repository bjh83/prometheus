cmake_minimum_required(VERSION 2.6)

project(prometheus)

enable_testing()

add_subdirectory(gtest-1.6.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(${PROJECT_SOURCE_DIR}/memory)
add_subdirectory(${PROJECT_SOURCE_DIR}/registers)
add_subdirectory(${PROJECT_SOURCE_DIR}/stages)
add_subdirectory(${PROJECT_SOURCE_DIR}/utils)

include_directories(
    ${PROJECT_SOURCE_DIR}/memory
    ${PROJECT_SOURCE_DIR}/registers
    ${PROJECT_SOURCE_DIR}/stages
    ${PROJECT_SOURCE_DIR}/utils
    )
