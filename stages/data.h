#ifndef DATA_H
#define DATA_H

#include <cstdint>
#include <memory>

namespace exec_cycle {

    class DecodedInstruction {
        public:
            DecodedInstruction(uint32_t instruction) {
                opcode_ = GetOpcode(instruction);
            }

            static uint32_t GetOpcode(uint32_t instruction) {
                return instruction >> 26;
            }

            uint32_t opcode() const { return opcode_; }
            virtual bool is_R_Instruction() const { return false; }
            virtual bool is_I_Instruction() const { return false; }
            virtual bool is_J_Instruction() const { return false; }
        private:
            uint32_t opcode_;
    };

    class R_Instruction : public DecodedInstruction {
        public:
            R_Instruction(uint32_t instruction) : DecodedInstruction(instruction) {
                left_ = (instruction << 6) >> 27;
                right_ = (instruction << 11) >> 27;
                dest_ = (instruction << 16) >> 27;
                shift_ = (instruction << 21) >> 27;
                func_ = (instruction << 26) >> 26;
            }
            uint32_t left() const { return left_; }
            uint32_t right() const { return right_; }
            uint32_t dest() const { return dest_; }
            uint32_t shift() const { return shift_; }
            uint32_t func() const { return func_; }
            virtual bool is_R_Instruction() const { return true; }
        private:
            uint32_t left_;
            uint32_t right_;
            uint32_t dest_;
            uint32_t shift_;
            uint32_t func_;
    };

    class I_Instruction : public DecodedInstruction {
        public:
            I_Instruction(uint32_t instruction) : DecodedInstruction(instruction) {
                source_ = (instruction << 6) >> 27;
                dest_ = (instruction << 11) >> 27;
                immed_ = (instruction << 16) >> 16;
            }
            uint32_t source() const { return source_; }
            uint32_t dest() const { return dest_; }
            uint32_t immed() const { return immed_; }
            virtual bool is_I_Instruction() const { return true; }
        private:
            uint32_t source_;
            uint32_t dest_;
            uint32_t immed_;
    };

    class J_Instruction : public DecodedInstruction {
        public:
            J_Instruction(uint32_t instruction) : DecodedInstruction(instruction) {
                address_ = (instruction << 6) >> 6;
            }
            uint32_t address() const { return address_; }
            virtual bool is_J_Instruction() const { return true; }
        private:
            uint32_t address_;
    };

    struct Data {
        public:
            explicit Data(uint32_t instruction) : raw_instruction(instruction) {}
            const uint32_t raw_instruction;
            std::unique_ptr<DecodedInstruction> decoded_instruction;
            uint32_t arithmetic_result_front;
            uint32_t arithmetic_result_back;
            uint32_t next_address;
    };

} // namespace exec_cycle
#endif // DATA_H
