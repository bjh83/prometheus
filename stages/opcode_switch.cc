#include "opcode_switch.h"
#include "interrupts/exceptions.h"

namespace exec_cycle {
    void OpcodeSwitch_R_InstructionBase::Switch(unique_ptr<Data> data) {
        const R_Instruction* instruction = static_cast<R_Instruction*>(data->decoded_instruction.get());
        switch(instruction->func()) {
            case 0x00: //sll
                Sll(unique_ptr<Data>(data.release()));
                break;
            case 0x02: //srl
                Srl(unique_ptr<Data>(data.release()));
                break;
            case 0x03: //sra
                Sra(unique_ptr<Data>(data.release()));
                break;
            case 0x04: //sllv
                Sllv(unique_ptr<Data>(data.release()));
                break;
            case 0x06: //srlv
                Srlv(unique_ptr<Data>(data.release()));
                break;
            case 0x07: //srav
                Srav(unique_ptr<Data>(data.release()));
                break;
            case 0x08: //jr
                Jr(unique_ptr<Data>(data.release()));
                break;
            case 0x09: //jalr
                Jalr(unique_ptr<Data>(data.release()));
                break;
            case 0x0c: //syscall
                Syscall(unique_ptr<Data>(data.release()));
                break;
            case 0x0d: //break
                Break(unique_ptr<Data>(data.release()));
                break;
            case 0x10: //mfhi
                Mfhi(unique_ptr<Data>(data.release()));
                break;
            case 0x11: //mthi
                Mthi(unique_ptr<Data>(data.release()));
                break;
            case 0x12: //mflo
                Mflo(unique_ptr<Data>(data.release()));
                break;
            case 0x13: //mtlo
                Mtlo(unique_ptr<Data>(data.release()));
                break;
            case 0x18: //mult
                Mult(unique_ptr<Data>(data.release()));
                break;
            case 0x19: //multu
                Multu(unique_ptr<Data>(data.release()));
                break;
            case 0x1a: //div
                Div(unique_ptr<Data>(data.release()));
                break;
            case 0x1b: //divu
                Divu(unique_ptr<Data>(data.release()));
                break;
            case 0x20: //add
                Add(unique_ptr<Data>(data.release()));
                break;
            case 0x21: //addu
                Addu(unique_ptr<Data>(data.release()));
                break;
            case 0x22: //sub
                Sub(unique_ptr<Data>(data.release()));
                break;
            case 0x23: //subu
                Subu(unique_ptr<Data>(data.release()));
                break;
            case 0x24: //and
                And(unique_ptr<Data>(data.release()));
                break;
            case 0x25: //or
                Or(unique_ptr<Data>(data.release()));
                break;
            case 0x26: //xor
                Xor(unique_ptr<Data>(data.release()));
                break;
            case 0x27: //nor
                Nor(unique_ptr<Data>(data.release()));
                break;
            case 0x2a: //slt
                Slt(unique_ptr<Data>(data.release()));
                break;
            case 0x2b: //sltu
                Sltu(unique_ptr<Data>(data.release()));
                break;
            default:
                controller_.Interrupt(interrupts::UndefinedInstruction(instruction->func()));
                break;
        }
    }

    void OpcodeSwitch_I_InstructionBase::Switch(unique_ptr<Data> data) {
        const I_Instruction* instruction = static_cast<I_Instruction*>(data->decoded_instruction.get());
        switch(instruction->opcode()) {
            case 0x01: //bltz
                switch(instruction->dest()) {
                    case 0x00: //bltz
                        Bltz(unique_ptr<Data>(data.release()));
                        break;
                    case 0x01: //bgez
                        Bgez(unique_ptr<Data>(data.release()));
                        break;
                    default:
                        controller_.Interrupt(interrupts::UndefinedInstruction(instruction->dest()));
                        break;
                }
                break;
            case 0x04: //beq
                Beq(unique_ptr<Data>(data.release()));
                break;
            case 0x05: //bne
                Bne(unique_ptr<Data>(data.release()));
                break;
            case 0x06: //blez
                Blez(unique_ptr<Data>(data.release()));
                break;
            case 0x07: //bgtz
                Bgtz(unique_ptr<Data>(data.release()));
                break;
            case 0x08: //addi
                Addi(unique_ptr<Data>(data.release()));
                break;
            case 0x09: //addiu
                Addiu(unique_ptr<Data>(data.release()));
                break;
            case 0x0a: //slti
                Slti(unique_ptr<Data>(data.release()));
                break;
            case 0x0b: //sltiu
                Sltiu(unique_ptr<Data>(data.release()));
                break;
            case 0x0c: //andi
                Andi(unique_ptr<Data>(data.release()));
                break;
            case 0x0d: //ori
                Ori(unique_ptr<Data>(data.release()));
                break;
            case 0x0e: //xori
                Xori(unique_ptr<Data>(data.release()));
                break;
            case 0x0f: //lui
                Lui(unique_ptr<Data>(data.release()));
                break;
            case 0x20: //lb
                Lb(unique_ptr<Data>(data.release()));
                break;
            case 0x21: //lh
                Lh(unique_ptr<Data>(data.release()));
                break;
            case 0x23: //lw
                Lw(unique_ptr<Data>(data.release()));
                break;
            case 0x24: //lbu
                Lbu(unique_ptr<Data>(data.release()));
                break;
            case 0x25: //lhu
                Lhu(unique_ptr<Data>(data.release()));
                break;
            case 0x28: //sb
                Sb(unique_ptr<Data>(data.release()));
                break;
            case 0x29: //sh
                Sh(unique_ptr<Data>(data.release()));
                break;
            case 0x2b: //sw
                Sw(unique_ptr<Data>(data.release()));
                break;
            case 0x31: //lwc1
                Lwc1(unique_ptr<Data>(data.release()));
            case 0x39: //swc1
                Swc1(unique_ptr<Data>(data.release()));
            default:
                controller_.Interrupt(interrupts::UndefinedInstruction(instruction->opcode()));
                break;
        }
    }

    void OpcodeSwitch_J_InstructionBase::Switch(unique_ptr<Data> data) {
        const J_Instruction* instruction = static_cast<J_Instruction*>(data->decoded_instruction.get());
        switch(instruction->opcode()) {
            case 0x02: //j
                J(unique_ptr<Data>(data.release()));
                break;
            case 0x03: //jal
                Jal(unique_ptr<Data>(data.release()));
                break;
            default:
                controller_.Interrupt(interrupts::UndefinedInstruction(instruction->opcode()));
                break;
        }
    }

} // namespace exec_cycle
