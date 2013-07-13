#include "stage.h"
#include "prometheus/registers/register.h"

namespace exec_cycle {
    using namespace registers;

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
    } // namespace

    class Execute::Execute_R_OpcodeSwitch : public OpcodeSwitch_R_InstructionBase {
        public:
            Execute_R_OpcodeSwitch(Stage& stage) : OpcodeSwitch_R_InstructionBase(stage) {}

        protected:
            virtual void Initialize(Data& data) {
                instruction = static_cast<R_Instruction*>(data.decoded_instruction.get());
                rs = &GetRegister(instruction->left());
                rt = &GetRegister(instruction->right());
                data.next_address = stage_.controller_.program_counter() + 4;
            }

            virtual void Add(unique_ptr<Data> data) {
                int32_t left = static_cast<int32_t>(rs->get());
                int32_t right = static_cast<int32_t>(rt->get());
                int32_t result = left + right;
                data->arithmetic_result_front = static_cast<uint32_t>(result);
                if((left < 0 && right < 0 && result > 0) || (left > 0 && right > 0 && result < 0)) {
                    stage_.controller_.Interrupt(interrupts::ArithmeticOverflowException());
                } else {
                    stage_.Output(data.release());
                }
            }

            virtual void Addu(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() + rt->get();
                stage_.Output(data.release());
            }

            virtual void And(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() & rt->get();
            }

            virtual void Break(unique_ptr<Data> data) {
                stage_.controller_.Interrupt(interrupts::BreakException());
            }

            virtual void Div(unique_ptr<Data> data) {
                data->arithmetic_result_front = static_cast<uint32_t>(static_cast<int32_t>(rs->get()) / static_cast<int32_t>(rt->get()));
                data->arithmetic_result_back = static_cast<uint32_t>(static_cast<int32_t>(rs->get()) % static_cast<int32_t>(rt->get()));
                stage_.Output(data.release());
            }

            virtual void Divu(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() / rt->get();
                data->arithmetic_result_back = rs->get() % rt->get();
                stage_.Output(data.release());
            }

            virtual void Jalr(unique_ptr<Data> data) {
                data->next_address = rs->get();
                stage_.Output(data.release());
            }

            virtual void Jr(unique_ptr<Data> data) {
                data->next_address = rs->get();
                stage_.Output(data.release());
            }

            virtual void Mfhi(unique_ptr<Data> data) {
                stage_.Output(data.release());
            }

            virtual void Mflo(unique_ptr<Data> data) {
                stage_.Output(data.release());
            }

            virtual void Mthi(unique_ptr<Data> data) {
                stage_.Output(data.release());
            }

            virtual void Mtlo(unique_ptr<Data> data) {
                stage_.Output(data.release());
            }

            virtual void Mult(unique_ptr<Data> data) {
                uint64_t result = static_cast<uint64_t>(static_cast<int64_t>(rs->get()) * static_cast<int64_t>(rt->get()));
                data->arithmetic_result_front = static_cast<uint32_t>(result >> 32);
                data->arithmetic_result_back = static_cast<uint32_t>(result);
                stage_.Output(data.release());
            }

            virtual void Multu(unique_ptr<Data> data) {
                uint64_t result = static_cast<uint64_t>(rs->get()) * static_cast<uint64_t>(rt->get());
                data->arithmetic_result_front = static_cast<uint32_t>(result >> 32);
                data->arithmetic_result_back = static_cast<uint32_t>(result);
                stage_.Output(data.release());
            }

            virtual void Nor(unique_ptr<Data> data) {
                data->arithmetic_result_front = ~(rs->get() | rt->get());
            }

            virtual void Or(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() | rt->get();
            }

            virtual void Sll(unique_ptr<Data> data) {
                data->arithmetic_result_front = rt->get() << instruction->shift();
                stage_.Output(data.release());
            }

            virtual void Sllv(unique_ptr<Data> data) {
                data->arithmetic_result_front = rt->get() << rs->get();
                stage_.Output(data.release());
            }

            virtual void Slt(unique_ptr<Data> data) {
                data->arithmetic_result_front = static_cast<int32_t>(rs->get()) < static_cast<int32_t>(rt->get()) ? 1 : 0;
                stage_.Output(data.release());
            }

            virtual void Sltu(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() < rt->get() ? 1 : 0;
                stage_.Output(data.release());
            }

            virtual void Sra(unique_ptr<Data> data) {
                data->arithmetic_result_front = ArithmeticShiftRight(rt->get(), instruction->shift());
                stage_.Output(data.release());
            }

            virtual void Srav(unique_ptr<Data> data) {
                data->arithmetic_result_front = ArithmeticShiftRight(rt->get(), rs->get());
                stage_.Output(data.release());
            }

            virtual void Srl(unique_ptr<Data> data) {
                data->arithmetic_result_front = rt->get() >> instruction->shift();
                stage_.Output(data.release());
            }

            virtual void Srlv(unique_ptr<Data> data) {
                data->arithmetic_result_front = rt->get() >> rs->get();
                stage_.Output(data.release());
            }

            virtual void Sub(unique_ptr<Data> data) {
                int32_t left = static_cast<int32_t>(rs->get());
                int32_t right = static_cast<int32_t>(rt->get());
                int32_t result = left - right;
                data->arithmetic_result_front = static_cast<uint32_t>(result);
                if((left < 0 && right > 0 && result > 0) || (left > 0 && right < 0 && result < 0)) {
                    stage_.controller_.Interrupt(interrupts::ArithmeticOverflowException());
                } else {
                    stage_.Output(data.release());
                }
            }

            virtual void Subu(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() - rt->get();
                stage_.Output(data.release());
            }

            virtual void Syscall(unique_ptr<Data> data) {
                stage_.controller_.Interrupt(interrupts::SyscallException());
            }

            virtual void Xor(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() ^ rt->get();
            }

        private:
            const R_Instruction* instruction;
            Register* rs;
            Register* rt;
    };

    class Execute::Execute_I_OpcodeSwitch : public OpcodeSwitch_I_InstructionBase {
        public:
            Execute_I_OpcodeSwitch(Stage& stage) : OpcodeSwitch_I_InstructionBase(stage) {}
        protected:
            virtual void Initialize(Data& data) {
                instruction = static_cast<I_Instruction*>(data.decoded_instruction.get());
                rs = &GetRegister(instruction->source());
                rt = &GetRegister(instruction->dest());
                immed = instruction->immed();
                data.next_address = stage_.controller_.program_counter() + 4;
            }

            virtual void Addi(unique_ptr<Data> data) {
                int32_t left = static_cast<int32_t>(rs->get());
                int32_t right = static_cast<int32_t>(immed);
                int32_t result = left + right;
                data->arithmetic_result_front = static_cast<uint32_t>(result);
                if((left < 0 && right < 0 && result > 0) || (left > 0 && right > 0 && result < 0)) {
                    stage_.controller_.Interrupt(interrupts::ArithmeticOverflowException());
                } else {
                    stage_.Output(data.release());
                }
            }

            virtual void Addiu(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() + immed;
                stage_.Output(data.release());
            }

            virtual void Andi(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() & immed;
                stage_.Output(data.release());
            }

            virtual void Beq(unique_ptr<Data> data) {
                if(rs->get() == rt->get()) {
                    data->arithmetic_result_front = stage_.controller_.program_counter() + immed;
                } else {
                    // Just go to the next address
                    data->arithmetic_result_front = data->next_address;
                }
                stage_.Output(data.release());
            }

            virtual void Bgez(unique_ptr<Data> data) {
                if(static_cast<int32_t>(rs->get()) >= 0) {
                    data->arithmetic_result_front = stage_.controller_.program_counter() + immed;
                } else {
                    // Just go to the next address
                    data->arithmetic_result_front = data->next_address;
                }
                stage_.Output(data.release());
            }

            virtual void Bgtz(unique_ptr<Data> data) {
                if(static_cast<int32_t>(rs->get()) > 0) {
                    data->arithmetic_result_front = stage_.controller_.program_counter() + immed;
                } else {
                    // Just go to the next address
                    data->arithmetic_result_front = data->next_address;
                }
                stage_.Output(data.release());
            }

            virtual void Blez(unique_ptr<Data> data) {
                if(static_cast<int32_t>(rs->get()) <= 0) {
                    data->arithmetic_result_front = stage_.controller_.program_counter() + immed;
                } else {
                    // Just go to the next address
                    data->arithmetic_result_front = data->next_address;
                }
                stage_.Output(data.release());
            }

            virtual void Bltz(unique_ptr<Data> data) {
                if(static_cast<int32_t>(rs->get()) < 0) {
                    data->arithmetic_result_front = stage_.controller_.program_counter() + immed;
                } else {
                    // Just go to the next address
                    data->arithmetic_result_front = data->next_address;
                }
                stage_.Output(data.release());
            }

            virtual void Bne(unique_ptr<Data> data) {
                if(rs->get() != rt->get()) {
                    data->arithmetic_result_front = stage_.controller_.program_counter() + immed;
                } else {
                    // Just go to the next address
                    data->arithmetic_result_front = data->next_address;
                }
                stage_.Output(data.release());
            }

            virtual void Lb(unique_ptr<Data> data) {
                data->arithmetic_result_front = immed + rs->get();
                stage_.Output(data.release());
            }

            virtual void Lbu(unique_ptr<Data> data) {
                data->arithmetic_result_front = immed + rs->get();
                stage_.Output(data.release());
            }

            virtual void Lh(unique_ptr<Data> data) {
                data->arithmetic_result_front = immed + rs->get();
                stage_.Output(data.release());
            }

            virtual void Lhu(unique_ptr<Data> data) {
                data->arithmetic_result_front = immed + rs->get();
                stage_.Output(data.release());
            }

            virtual void Lui(unique_ptr<Data> data) {
                data->arithmetic_result_front = immed << 16;
                stage_.Output(data.release());
            }

            virtual void Lw(unique_ptr<Data> data) {
                data->arithmetic_result_front = immed + rs->get();
                stage_.Output(data.release());
            }

            virtual void Lwc1(unique_ptr<Data> data) {
                data->arithmetic_result_front = immed + rs->get();
                stage_.Output(data.release());
            }

            virtual void Ori(unique_ptr<Data> data) {
                data->arithmetic_result_front = immed | rs->get();
                stage_.Output(data.release());
            }

            virtual void Sb(unique_ptr<Data> data) {
                data->arithmetic_result_front = immed + rs->get();
                data->arithmetic_result_back = rt->get();
                stage_.Output(data.release());
            }

            virtual void Slti(unique_ptr<Data> data) {
                data->arithmetic_result_front = static_cast<int32_t>(rs->get()) < static_cast<int32_t>(immed) ? 1 : 0;
                stage_.Output(data.release());
            }

            virtual void Sltiu(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() < immed ? 1 : 0;
                stage_.Output(data.release());
            }

            virtual void Sh(unique_ptr<Data> data) {
                data->arithmetic_result_front = immed + rs->get();
                data->arithmetic_result_back = rt->get();
                stage_.Output(data.release());
            }

            virtual void Sw(unique_ptr<Data> data) {
                data->arithmetic_result_front = immed + rs->get();
                data->arithmetic_result_back = rt->get();
                stage_.Output(data.release());
            }

            virtual void Swc1(unique_ptr<Data> data) {
                data->arithmetic_result_front = immed + rs->get();
                data->arithmetic_result_back = rt->get();
                stage_.Output(data.release());
            }

            virtual void Xori(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() ^ immed;
                stage_.Output(data.release());
            }

        private:
            const I_Instruction* instruction;
            Register* rs;
            Register* rt;
            uint32_t immed;
    };

    class Execute::Execute_J_OpcodeSwitch : public OpcodeSwitch_J_InstructionBase {
        public:
            Execute_J_OpcodeSwitch(Stage& stage) : OpcodeSwitch_J_InstructionBase(stage) {}

        protected:
            virtual void Initialize(Data& data) {
                const J_Instruction* instruction = static_cast<J_Instruction*>(data.decoded_instruction.get());
                address = instruction->address();
            }

            virtual void J(unique_ptr<Data> data) {
                data->arithmetic_result_front = address;
                stage_.Output(data.release());
            }

            virtual void Jal(unique_ptr<Data> data) {
                data->arithmetic_result_front = address;
                stage_.Output(data.release());
            }

        private:
            uint32_t address;
    };

    Execute::Execute(Controller& controller) : Stage(controller), r_switch_(new Execute_R_OpcodeSwitch(*this)),
        i_switch_(new Execute_I_OpcodeSwitch(*this)), j_switch_(new Execute_J_OpcodeSwitch(*this)) {}

    void Execute::Input(unique_ptr<Data> data) {
        if(data->decoded_instruction->is_R_Instruction()) {
            r_switch_->Switch(unique_ptr<Data>(data.release()));
        } else if(data->decoded_instruction->is_I_Instruction()) {
            i_switch_->Switch(unique_ptr<Data>(data.release()));
        } else if(data->decoded_instruction->is_J_Instruction()) {
            j_switch_->Switch(unique_ptr<Data>(data.release()));
        } else {
            // ERROR
        }
    }
} // namespace exec_cycle 
