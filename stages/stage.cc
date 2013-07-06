#include "stage.h"

namespace {
    uint32_t ArithmeticShiftRight(uint32_t to_shift_input, uint32_t shift_ammount_input) {
        int32_t to_shift = static_cast<int32_t>(to_shift_input);
        int32_t shift_ammount = static_cast<int32_t>(shift_ammount_input);
        int32_t result;
        if (to_shift < 0 && shift_ammount > 0)
            result = to_shift >> shift_ammount | ~(~0U >> shift_ammount);
        else
            result = to_shift >> shift_ammount;
        return static_cast<uint32_t>(result);
    }
}

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
            uint32_t instruction = controller.memory().get_uint32(controller.program_counter());
            Output(new Data(instruction));
        } else {
            utils::FatalError("Fetch should only be given null data");
        }
    }

    void Decode::Input(unique_ptr<Data> data) {
        switch(DecodedInstruction::GetOpcode(data->raw_instruction)) {
            case 0x00:
                data->decoded_instruction = unique_ptr<R_Instruction>(new R_Instruction(data->raw_instruction));
                Output(data.release());
                break;
            case 0x02:
            case 0x03:
                data->decoded_instruction = unique_ptr<J_Instruction>(new J_Instruction(data->raw_instruction));
                Output(data.release());
                break;
            case 0x01:
            case 0x04:
            case 0x05:
            case 0x06:
            case 0x07:
            case 0x08:
            case 0x09:
            case 0x0a:
            case 0x0b:
            case 0x0c:
            case 0x0d:
            case 0x0e:
            case 0x0f:
            case 0x20:
            case 0x21:
            case 0x23:
            case 0x24:
            case 0x25:
            case 0x28:
            case 0x29:
            case 0x2b:
            case 0x31:
            case 0x39:
                data->decoded_instruction = unique_ptr<I_Instruction>(new I_Instruction(data->raw_instruction));
                Output(data.release());
                break;
            default:
                controller.Interrupt(interrupts::UndefinedInstruction(data->raw_instruction));
                break;
        }
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
        data->next_address = controller.program_counter() + 4;
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
                controller.Interrupt(interrupts::SyscallException());
                return;
            case 0x0d: //break
                controller.Interrupt(interrupts::BreakException());
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
                    controller.Interrupt(interrupts::ArithmeticOverflowException());
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
                    controller.Interrupt(interrupts::ArithmeticOverflowException());
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
                controller.Interrupt(interrupts::UndefinedInstruction(data->raw_instruction));
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
