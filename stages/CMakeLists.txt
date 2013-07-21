add_subdirectory(interrupts)
include_directories(interrupts)

add_library(stages
    controller.cc
    execute.cc
    memread.cc
    memwrite.cc
    opcode_switch.cc
    stage.cc
    write_back.cc
    )

target_link_libraries(stages interrupts)
