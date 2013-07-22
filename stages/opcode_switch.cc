#include "opcode_switch.h"
#include "interrupts/exceptions.h"

namespace exec_cycle {
    void OpcodeSwitchBase::Switch(unique_ptr<Data> data) {
        Initialize(*data.get());
        InternalSwitch(unique_ptr<Data>(data.release()));
    }

    void OpcodeSwitch_R_InstructionBase::InternalSwitch(unique_ptr<Data> data) {
        const R_Instruction* instruction = static_cast<R_Instruction*>(data->decoded_instruction.get());
        switch(static_cast<R_Instruction::Func>(instruction->func())) {
            case R_Instruction::ADD:
                Add(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::ADDU:
                Addu(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::AND:
                And(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::BREAK:
                Break(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::DIV:
                Div(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::DIVU:
                Divu(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::JALR:
                Jalr(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::JR:
                Jr(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::MFHI:
                Mfhi(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::MFLO:
                Mflo(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::MTHI:
                Mthi(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::MTLO:
                Mtlo(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::MULT:
                Mult(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::MULTU:
                Multu(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::NOR:
                Nor(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::OR:
                Or(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::SLL:
                Sll(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::SLLV:
                Sllv(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::SLT:
                Slt(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::SLTU:
                Sltu(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::SRA:
                Sra(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::SRAV:
                Srav(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::SRL:
                Srl(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::SRLV:
                Srlv(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::SUB:
                Sub(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::SUBU:
                Subu(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::SYSCALL:
                Syscall(unique_ptr<Data>(data.release()));
                break;
            case R_Instruction::XOR:
                Xor(unique_ptr<Data>(data.release()));
                break;
        }
    }

    void OpcodeSwitch_I_InstructionBase::InternalSwitch(unique_ptr<Data> data) {
        const I_Instruction* instruction = static_cast<I_Instruction*>(data->decoded_instruction.get());
        switch(static_cast<I_Instruction::Opcode>(instruction->opcode())) {
            case I_Instruction::ADDI:
                Addi(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::ADDIU:
                Addiu(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::ANDI:
                Andi(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::BEQ:
                Beq(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::BGEZ_BLTZ:
                switch(static_cast<I_Instruction::ExtendedOpcode>(instruction->rt())) {
                    case I_Instruction::BGEZ:
                        Bgez(unique_ptr<Data>(data.release()));
                        break;
                    case I_Instruction::BLTZ:
                        Bltz(unique_ptr<Data>(data.release()));
                        break;
                }
            case I_Instruction::BGTZ:
                Bgtz(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::BLEZ:
                Blez(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::BNE:
                Bne(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::LB:
                Lb(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::LBU:
                Lbu(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::LH:
                Lh(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::LHU:
                Lhu(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::LUI:
                Lui(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::LW:
                Lw(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::LWC1:
                Lwc1(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::ORI:
                Ori(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::SB:
                Sb(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::SLTI:
                Slti(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::SLTIU:
                Sltiu(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::SH:
                Sh(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::SW:
                Sw(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::SWC1:
                Swc1(unique_ptr<Data>(data.release()));
                break;
            case I_Instruction::XORI:
                Xori(unique_ptr<Data>(data.release()));
                break;
        }
    }

    void OpcodeSwitch_J_InstructionBase::InternalSwitch(unique_ptr<Data> data) {
        const J_Instruction* instruction = static_cast<J_Instruction*>(data->decoded_instruction.get());
        switch(static_cast<J_Instruction::Opcode>(instruction->opcode())) {
            case J_Instruction::J:
                J(unique_ptr<Data>(data.release()));
                break;
            case J_Instruction::JAL:
                Jal(unique_ptr<Data>(data.release()));
                break;
        }
    }

} // namespace exec_cycle
