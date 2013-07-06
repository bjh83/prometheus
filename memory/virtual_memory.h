#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include <cstdint>
#include "physical_memory.h"

namespace memory {
    class VirtualMemory {
        public:
            VirtualMemory() {}
            ~VirtualMemory() {}
            static bool IsValid(uint32_t address);
            uint8_t get_uint8(uint32_t address) const;
            uint32_t get_uint32(uint32_t address) const;
            void set(uint32_t address, uint8_t value);
            void set(uint32_t address, uint32_t value);
            
            static const uint32_t kKSEG0Start = 0x80000000;
            static const uint32_t kKSEG0End = 0x9fc02fff;
            static const uint32_t kKSEG1Start = 0xa0000000;
            static const uint32_t kKSEG1End = 0xbfc02fff;
        private:
            PhysicalMemory memory_;
    };
}

#endif // VIRTUAL_MEMORY_H
