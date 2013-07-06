#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include <cstdint>

namespace memory {
    class PhysicalMemory {
        public:
            PhysicalMemory() {}
            ~PhysicalMemory();
            uint8_t get(uint32_t address) const;
            void set(uint32_t address, uint8_t value);

            static const uint32_t kRAMStart = 0x00000000;
            static const uint32_t kRAMEnd = 0x0001ffff;
            static const uint32_t kProgramFlashStart = 0x1d000000;
            static const uint32_t kProgramFlashEnd = 0x1d07ffff;
            static const uint32_t kSFRStart = 0x1f800000;
            static const uint32_t kSFREnd = 0x1f8fffff;
            static const uint32_t kBootFlashStart = 0x1fc00000;
            static const uint32_t kBootFlashEnd = 0x1fc02fef;
            static const uint32_t kDeviceConfigRegsStart = 0x1fc02ff0;
            static const uint32_t kDeviceConfigRegsEnd = 0x1fc02fff;

        private:
            uint8_t* RAM = new uint8_t[kRAMEnd - kRAMStart + 1];
            uint8_t* ProgramFlash = new uint8_t[kProgramFlashEnd - kProgramFlashStart + 1];
            uint8_t* SFR = new uint8_t[kSFREnd - kSFRStart + 1];
            uint8_t* BootFlash = new uint8_t[kBootFlashEnd - kBootFlashStart + 1];
            uint8_t* DeviceConfigRegs = new uint8_t[kDeviceConfigRegsEnd - kDeviceConfigRegsStart + 1];
    };
}
#endif // PHYSICAL_MEMORY_H
