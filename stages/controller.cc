#include "controller.h"

namespace exec_cycle {
    Controller::Controller() : program_counter_(VirtualMemory::kKSEG0Start + 
            PhysicalMemory::kProgramFlashStart) {
        fetch_stage_ = unique_ptr<Fetch>(new Fetch(*this));
        fetch_stage_->Connect(new Decode(*this));
        fetch_stage_->Connect(new Execute(*this));
        fetch_stage_->Connect(new MemRead(*this));
        fetch_stage_->Connect(new MemWrite(*this));
        fetch_stage_->Connect(new WriteBack(*this));
    }

    void Controller::Start() {
        for(;;) {
            fetch_stage_->Input(unique_ptr<Data>());
            check_error();
        }
    }
} // namespace exec_cycle
