#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <cstdint>
#include <memory>

#include "prometheus/memory/virtual_memory.h"
#include "data.h"
#include "stage.h"
#include "interrupts/exceptions.h"

namespace exec_cycle {
    using namespace std;
    using namespace memory;

    class Controller {
        public:
            Controller();
            void Start();
            void Interrupt(interrupts::Exception& exception);
            const VirtualMemory& memory() const { return memory_; }
            VirtualMemory& mutable_memory() { return memory_; }
            const uint32_t& program_counter() const { return program_counter_; }
            uint32_t& mutable_program_counter() { return program_counter_; }
        private:
            void check_error();
            VirtualMemory memory_;
            uint32_t program_counter_;
            unique_ptr<Fetch> fetch_stage_;
    };
}
#endif // CONTROLLER_H
