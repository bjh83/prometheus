add_library(memory
    virtual_memory.cc
    physical_memory.cc
    )

add_executable(physical_memory_test physical_memory_test.cc)
target_link_libraries(physical_memory_test
    memory
    gtest
    gtest_main)

add_test(physical_memory_test physical_memory_test)

add_executable(virtual_memory_test virtual_memory_test.cc)
target_link_libraries(virtual_memory_test
    memory
    utils
    gtest
    gtest_main)

add_test(virtual_memory_test virtual_memory_test)
