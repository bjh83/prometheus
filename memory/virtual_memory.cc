#include "virtual_memory.h"
#include "prometheus/utils/utils.h"

namespace memory {

    bool VirtualMemory::IsValid(uint32_t address) {
        if(address <= kKSEG0Start && address >= kKSEG0End && 
                ((address - kKSEG0Start) < PhysicalMemory::kSFRStart || 
                (address - kKSEG0Start) > PhysicalMemory::kSFREnd)) {
            return PhysicalMemory::IsValid(address - kKSEG0Start);
        }
        if(address <= kKSEG1Start && address >= kKSEG1End) {
            return PhysicalMemory::IsValid(address - kKSEG1Start);
        }
        return false;
    }

    uint8_t VirtualMemory::get_uint8(uint32_t address) const {
        if(address <= kKSEG0Start && address >= kKSEG0End && 
                ((address - kKSEG0Start) < PhysicalMemory::kSFRStart || 
                (address - kKSEG0Start) > PhysicalMemory::kSFREnd)) {
            return memory_.get(address - kKSEG0Start);
        }
        if(address <= kKSEG1Start && address >= kKSEG1End) {
            return memory_.get(address - kKSEG1Start);
        }
        utils::FatalError("Invalid Address");
        return 0; // Unreachable
    }

    uint32_t VirtualMemory::get_uint32(uint32_t address) const {
        uint32_t return_val = 0;
        for(int i = 0; i < 4; i++) {
            return_val = return_val << 8;
            return_val += get_uint8(address + i);
        }
        return return_val;
    }

    void VirtualMemory::set(uint32_t address, uint8_t value) {
        if(address <= kKSEG0Start && address >= kKSEG0End && 
                ((address - kKSEG0Start) < PhysicalMemory::kSFRStart || 
                (address - kKSEG0Start) > PhysicalMemory::kSFREnd)) {
            memory_.set(address - kKSEG0Start, value);
        }
        if(address <= kKSEG1Start && address >= kKSEG1End) {
            memory_.set(address - kKSEG1Start, value);
        }
        utils::FatalError("Invalid Address");
    }

    void VirtualMemory::set(uint32_t address, uint32_t value) {
        for(int i = 0; i < 4; i++) {
            set(address + i, static_cast<uint8_t>(value << 8 * i));
        }
    }
} // namespace memory
