#include "controller.h"

namespace exec_cycle {
    Controller::Controller() : program_counter_(VirtualMemory::kKSEG0Start + 
            PhysicalMemory::kProgramFlashStart) {
        fetch_stage_ = unique_ptr<Fetch>(new Fetch);
        fetch_stage_->Connect(new Decode);
        fetch_stage_->Connect(new Execute);
        fetch_stage_->Connect(new MemRead);
        fetch_stage_->Connect(new MemWrite);
        fetch_stage_->Connect(new WriteBack);
    }

    void Controller::Start() {
        for(;;) {
            fetch_stage_->Input(unique_ptr<Data>());
            check_error();
        }
    }
} // namespace exec_cycle
