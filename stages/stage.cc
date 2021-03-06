#include "stage.h"

namespace exec_cycle {
    using namespace std;

    void Stage::Connect(Stage* stage) {
        if(next_stage) {
            next_stage->Connect(stage);
        } else {
            next_stage = unique_ptr<Stage>(stage);
        }
    }

    void Fetch::Input(unique_ptr<Data> data) { // data is null so do not do anything with it
        if(data) {
            uint32_t instruction = controller_.memory().get_uint32(controller_.program_counter());
            Output(new Data(instruction));
        } else {
            utils::FatalError("Fetch should only be given null data");
        }
    }

    void Decode::Input(unique_ptr<Data> data) {
        data->decoded_instruction = DecodedInstruction::DecodeInstruction(data->raw_instruction);
        switch(data->decoded_instruction->GetType()) {
            case DecodedInstruction::R_Type:
                const R_Instruction* r_instruction = static_cast<R_Instruction*>(data->decoded_instruction.get());
                data->rs = registers::GetRegister(r_instruction->rs()).get();
                data->rt = registers::GetRegister(r_instruction->rt()).get();
                break;
            case DecodedInstruction::I_Type:
                const I_Instruction* i_instruction = static_cast<I_Instruction*>(data->decoded_instruction.get());
                data->rs = registers::GetRegister(i_instruction->rs()).get();
                data->rt = registers::GetRegister(i_instruction->rt()).get();
                break;
            case DecodedInstruction::J_Type:
                break;
            case DecodedInstruction::Invalid:
                controller_.Interrupt(interrupts::UndefinedInstruction(data->raw_instruction));
                return;
        }
        Output(data.release());
    }

    void Execute::Input(unique_ptr<Data> data) {
        if(data->decoded_instruction->is_R_Instruction()) {
            Execute_R(unique_ptr<Data>(data.release()));
        } else if(data->decoded_instruction->is_I_Instruction()) {
            Execute_I(unique_ptr<Data>(data.release()));
        } else if(data->decoded_instruction->is_J_Instruction()) {
            Execute_J(unique_ptr<Data>(data.release()));
        }
    }

    void Execute::Execute_R(unique_ptr<Data> data) {
        using namespace registers;
        const R_Instruction* instruction = static_cast<R_Instruction*>(data->decoded_instruction.get());
        Register& rs = registers::GetRegister(instruction->left());
        Register& rt = registers::GetRegister(instruction->right());
        data->next_address = controller_.program_counter() + 4;
        switch(instruction->func()) {
            case 0x00: //sll
                data->arithmetic_result_front = rt.get() << instruction->shift();
                Output(data.release());
                return;
            case 0x02: //srl
                data->arithmetic_result_front = rt.get() >> instruction->shift();
                Output(data.release());
                return;
            case 0x03: //sra
                data->arithmetic_result_front = ArithmeticShiftRight(rt.get(), instruction->shift());
                Output(data.release());
                return;
            case 0x04: //sllv
                data->arithmetic_result_front = rt.get() << rs.get();
                Output(data.release());
                return;
            case 0x06: //srlv
                data->arithmetic_result_front = rt.get() >> rs.get();
                Output(data.release());
                return;
            case 0x07: //srav
                data->arithmetic_result_front = ArithmeticShiftRight(rt.get(), rs.get());
                Output(data.release());
                return;
            case 0x08: //jr
                data->next_address = rs.get();
                Output(data.release());
                return;
            case 0x09: //jalr
                data->next_address = rs.get();
                Output(data.release());
                return;
            case 0x0c: //syscall
                controller_.Interrupt(interrupts::SyscallException());
                return;
            case 0x0d: //break
                controller_.Interrupt(interrupts::BreakException());
                return;
            case 0x10: //mfhi
                Output(data.release());
                return;
            case 0x11: //mthi
                Output(data.release());
                return;
            case 0x12: //mflo
                Output(data.release());
                return;
            case 0x13: //mtlo
                Output(data.release());
                return;
            case 0x18: { //mult
                uint64_t result = static_cast<uint64_t>(static_cast<int64_t>(rs.get()) * static_cast<int64_t>(rt.get()));
                data->arithmetic_result_front = static_cast<uint32_t>(result >> 32);
                data->arithmetic_result_back = static_cast<uint32_t>(result);
                Output(data.release());
                return;
                       }
            case 0x19: { //multu
                uint64_t result = static_cast<uint64_t>(rs.get()) * static_cast<uint64_t>(rt.get());
                data->arithmetic_result_front = static_cast<uint32_t>(result >> 32);
                data->arithmetic_result_back = static_cast<uint32_t>(result);
                Output(data.release());
                return;
                       }
            case 0x1a: //div
                data->arithmetic_result_front = static_cast<uint32_t>(static_cast<int32_t>(rs.get()) / static_cast<int32_t>(rt.get()));
                data->arithmetic_result_back = static_cast<uint32_t>(static_cast<int32_t>(rs.get()) % static_cast<int32_t>(rt.get()));
                Output(data.release());
                return;
            case 0x1b: //divu
                data->arithmetic_result_front = rs.get() / rt.get();
                data->arithmetic_result_back = rs.get() % rt.get();
                Output(data.release());
                return;
            case 0x20: { //add
                int32_t left = static_cast<int32_t>(rs.get());
                int32_t right = static_cast<int32_t>(rt.get());
                int32_t result = left + right;
                data->arithmetic_result_front = static_cast<uint32_t>(result);
                if((left < 0 && right < 0 && result > 0) || (left > 0 && right > 0 && result < 0)) {
                    controller_.Interrupt(interrupts::ArithmeticOverflowException());
                } else {
                    Output(data.release());
                }
                return;
                       }
            case 0x21: //addu
                data->arithmetic_result_front = rs.get() + rt.get();
                Output(data.release());
            case 0x22: { //sub
                int32_t left = static_cast<int32_t>(rs.get());
                int32_t right = static_cast<int32_t>(rt.get());
                int32_t result = left - right;
                data->arithmetic_result_front = static_cast<uint32_t>(result);
                if((left < 0 && right > 0 && result > 0) || (left > 0 && right < 0 && result < 0)) {
                    controller_.Interrupt(interrupts::ArithmeticOverflowException());
                } else {
                    Output(data.release());
                }
                return;
                       }
            case 0x23: //subu
                data->arithmetic_result_front = rs.get() - rt.get();
                Output(data.release());
            case 0x24: //and
                data->arithmetic_result_front = rs.get() & rt.get();
                Output(data.release());
                return;
            case 0x25: //or
                data->arithmetic_result_front = rs.get() | rt.get();
                Output(data.release());
                return;
            case 0x26: //xor
                data->arithmetic_result_front = rs.get() ^ rt.get();
                Output(data.release());
                return;
            case 0x27: //nor
                data->arithmetic_result_front = ~(rs.get() | rt.get());
                Output(data.release());
                return;
            case 0x2a: //slt
                data->arithmetic_result_front = static_cast<int32_t>(rs.get()) < static_cast<int32_t>(rt.get()) ? 1 : 0;
                Output(data.release());
                return;
            case 0x2b: //sltu
                data->arithmetic_result_front = rs.get() < rt.get() ? 1 : 0;
                Output(data.release());
                return;
            default:
                controller_.Interrupt(interrupts::UndefinedInstruction(data->raw_instruction));
                return;
        }
    }

    void Execute::Execute_I(unique_ptr<Data> data) {
        using namespace registers;
        const I_Instruction* instruction = static_cast<I_Instruction*>(data->decoded_instruction.get());
        Register& rs = registers::GetRegister(instruction->source());
        Register& rt = registers::GetRegister(instruction->dest());
        switch(instruction->opcode()) {
        }
    }

    void Execute::Execute_J(unique_ptr<Data> data) {
        using namespace registers;
        const J_Instruction* instruction = static_cast<J_Instruction*>(data->decoded_instruction.get());
        switch(instruction->opcode()) {
        }
    }

    void MemRead::Input(unique_ptr<Data> data) {
    }

    void MemWrite::Input(unique_ptr<Data> data) {
    }

    void WriteBack::Input(unique_ptr<Data> data) {
    }
} // namespace exec_cycle
