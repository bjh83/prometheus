#include "data.h"

namespace exec_cycle {
    using std::unique_ptr;

    unique_ptr<DecodedInstruction> DecodedInstruction::DecodeInstruction(uint32_t instruction) {
        unique_ptr<DecodedInstruction> decoded_instruction;
        uint32_t opcode = GetOpcode(instruction);
        if(opcode == 0x00) {
            decoded_instruction = unique_ptr<R_Instruction>(new R_Instruction(instruction));
            if(!decoded_instruction->IsValid()) {
                decoded_instruction = unique_ptr<InvalidInstruction>(new InvalidInstruction(instruction));
            }
        } else if(I_Instruction::IsOpcodeValid(opcode)) {
            decoded_instruction = unique_ptr<I_Instruction>(new I_Instruction(instruction));
            if(!decoded_instruction->IsValid()) {
                decoded_instruction = unique_ptr<InvalidInstruction>(new InvalidInstruction(instruction));
            }
        } else if(J_Instruction::IsOpcodeValid(opcode)) {
            decoded_instruction = unique_ptr<J_Instruction>(new J_Instruction(instruction));
        } else {
            decoded_instruction = unique_ptr<InvalidInstruction>(new InvalidInstruction(instruction));
        }
        return decoded_instruction;
    }

    R_Instruction::R_Instruction(uint32_t instruction) : DecodedInstruction(instruction) {
        rs_ = (instruction << 6) >> 27;
        rt_ = (instruction << 11) >> 27;
        rd_ = (instruction << 16) >> 27;
        shift_ = (instruction << 21) >> 27;
        func_ = (instruction << 26) >> 26;
        is_valid_ = IsFuncValid(func_) && registers::IsValid(rs_) && registers::IsValid(rt_) && registers::IsValid(rd_);
    }

    bool R_Instruction::IsFuncValid(uint32_t func) {
        switch(func) {
            case ADD:
            case ADDU:
            case AND:
            case BREAK:
            case DIV:
            case DIVU:
            case JALR:
            case JR:
            case MFHI:
            case MFLO:
            case MTHI:
            case MTLO:
            case MULT:
            case MULTU:
            case NOR:
            case OR:
            case SLL:
            case SLLV:
            case SLT:
            case SLTU:
            case SRA:
            case SRAV:
            case SRL:
            case SRLV:
            case SUB:
            case SUBU:
            case SYSCALL:
            case XOR:
                return true;
            default:
                return false;
        }
    }

    I_Instruction::I_Instruction(uint32_t instruction) : DecodedInstruction(instruction) {
        rs_ = (instruction << 6) >> 27;
        rt_ = (instruction << 11) >> 27;
        immed_ = (instruction << 16) >> 16;
        is_valid_ = IsExtendedOpcodeValid(static_cast<Opcode>(opcode()), rt_) && registers::IsValid(rs_) && registers::IsValid(rt_);
    }

    bool I_Instruction::IsOpcodeValid(uint32_t opcode) {
        switch(opcode) {
            case ADDI:
            case ADDIU:
            case ANDI:
            case BEQ:
            case BGEZ_BLTZ:
            case BGTZ:
            case BLEZ:
            case BNE:
            case LB:
            case LBU:
            case LH:
            case LHU:
            case LUI:
            case LW:
            case LWC1:
            case ORI:
            case SB:
            case SLTI:
            case SLTIU:
            case SH:
            case SW:
            case SWC1:
            case XORI:
                return true;
            default:
                return false;
        }
    }

    bool I_Instruction::IsExtendedOpcodeValid(Opcode opcode, uint32_t rt) {
        switch(opcode) {
            case BGEZ_BLTZ:
                if(rt == BGEZ || rt == BLTZ) {
                    return true;
                }
                break;
            case BGTZ:
                if(rt == 0x00) {
                    return true;
                }
                break;
            case BLEZ:
                if(rt == 0x00) {
                    return true;
                }
                break;
            default:
                return true;
        }
        return false;
    }

    J_Instruction::J_Instruction(uint32_t instruction) : DecodedInstruction(instruction) {
        address_ = (instruction << 6) >> 6;
    }

    bool J_Instruction::IsOpcodeValid(uint32_t opcode) {
        switch(opcode) {
            case J:
            case JAL:
                return true;
            default:
                return false;
        }
    }

} // namespace exec_cycle
