#include "physical_memory.h"
#include "prometheus/utils/utils.h"

namespace memory {
    PhysicalMemory::~PhysicalMemory() {
        delete RAM;
        delete ProgramFlash;
        delete SFR;
        delete BootFlash;
        delete DeviceConfigRegs;
    }

    bool PhysicalMemory::IsValid(uint32_t address) {
        if(address <= kRAMEnd) {
            return true;
        }
        if(address >= kProgramFlashStart && address <= kProgramFlashEnd) {
            return true;
        }
        if(address >= kSFRStart && address <= kSFREnd) {
            return true;
        }
        if(address >= kBootFlashStart && address <= kBootFlashEnd) {
            return true;
        }
        if(address >= kDeviceConfigRegsStart && address <= kBootFlashEnd) {
            return true;
        }
        return false;
    }

    uint8_t PhysicalMemory::get(uint32_t address) const {
        if(address <= kRAMEnd) {
            return RAM[address];
        }
        if(address >= kProgramFlashStart && address <= kProgramFlashEnd) {
            return ProgramFlash[address];
        }
        if(address >= kSFRStart && address <= kSFREnd) {
            return SFR[address];
        }
        if(address >= kBootFlashStart && address <= kBootFlashEnd) {
            return BootFlash[address];
        }
        if(address >= kDeviceConfigRegsStart && address <= kBootFlashEnd) {
            return DeviceConfigRegs[address];
        }
        utils::FatalError("Invalid address");
        return 0; // Unreachable
    }

    void PhysicalMemory::set(uint32_t address, uint8_t value) {
        if(address <= kRAMEnd) {
            RAM[address] = value;
            return;
        }
        if(address >= kProgramFlashStart && address <= kProgramFlashEnd) {
            ProgramFlash[address] = value;
            return;
        }
        if(address >= kSFRStart && address <= kSFREnd) {
            SFR[address] = value;
            return;
        }
        if(address >= kBootFlashStart && address <= kBootFlashEnd) {
            BootFlash[address] = value;
            return;
        }
        if(address >= kDeviceConfigRegsStart && address <= kDeviceConfigRegsEnd) {
            DeviceConfigRegs[address] = value;
            return;
        }
        utils::FatalError("Invalid address");
    }
} // namespace memory
