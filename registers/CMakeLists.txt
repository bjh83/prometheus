add_library(registers register.cc)

add_executable(register_test register_test.cc)
target_link_libraries(register_test
    registers
    gtest
    gtest_main
    )

add_test(register_test register_test)
