#ifndef DATA_H
#define DATA_H

#include <cstdint>
#include <memory>

#include "prometheus/registers/register.h"

namespace exec_cycle {

    class DecodedInstruction {
        public:
            DecodedInstruction(uint32_t instruction) {
                opcode_ = GetOpcode(instruction);
            }

            enum InstructionType {
                R_Type,
                I_Type,
                J_Type,
                Invalid,
            };

            static uint32_t GetOpcode(uint32_t instruction) {
                return instruction >> 26;
            }

            static std::unique_ptr<DecodedInstruction> DecodeInstruction(uint32_t instruction);

            uint32_t opcode() const { return opcode_; }
            virtual InstructionType GetType() = 0;
            virtual bool IsValid() = 0;
        private:
            uint32_t opcode_;
    };

    class R_Instruction : public DecodedInstruction {
        public:
            R_Instruction(uint32_t instruction);

            enum Func {
                ADD = 0x20,
                ADDU = 0x21,
                AND = 0x24,
                BREAK = 0x0d,
                DIV = 0x1a,
                DIVU = 0x1b,
                JALR = 0x09,
                JR = 0x08,
                MFHI = 0x10,
                MFLO = 0x12,
                MTHI = 0x11,
                MTLO = 0x13,
                MULT = 0x18,
                MULTU = 0x19,
                NOR = 0x27,
                OR = 0x25,
                SLL = 0x00,
                SLLV = 0x04,
                SLT = 0x2a,
                SLTU = 0x2b,
                SRA = 0x03,
                SRAV = 0x07,
                SRL = 0x02,
                SRLV = 0x06,
                SUB = 0x22,
                SUBU = 0x23,
                SYSCALL = 0x0c,
                XOR = 0x26,
            };

            uint32_t rs() const { return rs_; }
            uint32_t rt() const { return rt_; }
            uint32_t rd() const { return rd_; }
            uint32_t shift() const { return shift_; }
            uint32_t func() const { return func_; }
            virtual InstructionType GetType() { return R_Type; }
            virtual bool IsValid() { return is_valid_; }
            static bool IsFuncValid(uint32_t func);

        private:
            uint32_t rs_;
            uint32_t rt_;
            uint32_t rd_;
            uint32_t shift_;
            uint32_t func_;
            bool is_valid_;
    };

    class I_Instruction : public DecodedInstruction {
        public:
            I_Instruction(uint32_t instruction);

            enum Opcode {
                ADDI = 0x08,
                ADDIU = 0x09,
                ANDI = 0x0c,
                BEQ = 0x04,
                BGEZ_BLTZ = 0x01,
                BGTZ = 0x07,
                BLEZ = 0x06,
                BNE = 0x05,
                LB = 0x20,
                LBU = 0x24,
                LH = 0x21,
                LHU = 0x25,
                LUI = 0x0f,
                LW = 0x23,
                LWC1 = 0x31,
                ORI = 0x0d,
                SB = 0x28,
                SLTI = 0x0a,
                SLTIU = 0x0b,
                SH = 0x29,
                SW = 0x2b,
                SWC1 = 0x39,
                XORI = 0x0e,
            };

            enum ExtendedOpcode {
                BGEZ = 0x01,
                BLTZ = 0x00,
            };

            uint32_t rs() const { return rs_; }
            uint32_t rt() const { return rt_; }
            uint32_t immed() const { return immed_; }
            virtual InstructionType GetType() { return I_Type; }
            virtual bool IsValid() { return is_valid_; }
            static bool IsOpcodeValid(uint32_t opcode);
            static bool IsExtendedOpcodeValid(Opcode opcode, uint32_t rt);

        private:
            uint32_t rs_;
            uint32_t rt_;
            uint32_t immed_;
            bool is_valid_;
    };

    class J_Instruction : public DecodedInstruction {
        public:
            J_Instruction(uint32_t instruction);

            enum Opcode {
                J = 0x02,
                JAL = 0x03,
            };

            uint32_t address() const { return address_; }
            virtual InstructionType GetType() { return J_Type; }
            virtual bool IsValid() { return true; }
            static bool IsOpcodeValid(uint32_t opcode);

        private:
            uint32_t address_;
    };

    class InvalidInstruction : public DecodedInstruction {
        public:
            InvalidInstruction(uint32_t instruction) : DecodedInstruction(instruction) {}

            virtual InstructionType GetType() { return Invalid; }
            virtual bool IsValid() { return false; }
    };

    struct Data {
        public:
            explicit Data(uint32_t instruction) : raw_instruction(instruction) {}
            const uint32_t raw_instruction;
            std::unique_ptr<DecodedInstruction> decoded_instruction;
            uint32_t rs;
            uint32_t rt;
            uint32_t arithmetic_result_front;
            uint32_t arithmetic_result_back;
            uint32_t next_address;
    };

} // namespace exec_cycle
#endif // DATA_H
