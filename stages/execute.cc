#include "stage.h"
#include "prometheus/registers/register.h"

namespace exec_cycle {
    using namespace registers;

    class Execute::Execute_R_OpcodeSwitch : public OpcodeSwitch_R_InstructionBase {
        public:
            virtual void Switch(unique_ptr<Data> data) {
                instruction = static_cast<R_Instruction*>(data->decoded_instruction.get());
                rs = &GetRegister(instruction->left());
                rt = &GetRegister(instruction->right());
                data->next_address = controller_.program_counter() + 4;
                OpcodeSwitch_R_InstructionBase::Switch(unique_ptr<Data>(data.release()));
            }
        protected:
            virtual void Add(unique_ptr<Data> data) {
                int32_t left = static_cast<int32_t>(rs->get());
                int32_t right = static_cast<int32_t>(rt->get());
                int32_t result = left + right;
                data->arithmetic_result_front = static_cast<uint32_t>(result);
                if((left < 0 && right < 0 && result > 0) || (left > 0 && right > 0 && result < 0)) {
                    controller_.Interrupt(interrupts::ArithmeticOverflowException());
                } else {
                    Output(data.release());
                }
            }

            virtual void Addu(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() + rt->get;
                Output(data.release());
            }

            virtual void And(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs.get() & rt.get();
            }

            virtual void Break(unique_ptr<Data> data) {
                controller_.Interrupt(interrupts::BreakException());
            }

            virtual void Div(unique_ptr<Data> data) {
                data->arithmetic_result_front = static_cast<uint32_t>(static_cast<int32_t>(rs->get()) / static_cast<int32_t>(rt->get()));
                data->arithmetic_result_back = static_cast<uint32_t>(static_cast<int32_t>(rs->get()) % static_cast<int32_t>(rt->get()));
                Output(data.release());
            }

            virtual void Divu(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() / rt->get();
                data->arithmetic_result_back = rs->get() % rt->get();
                Output(data.release());
            }

            virtual void Jalr(unique_ptr<Data> data) {
                data->next_address = rs->get();
                Output(data.release());
            }

            virtual void Jr(unique_ptr<Data> data) {
                data->next_address = rs->get();
                Output(data.release());
            }

            virtual void Mfhi(unique_ptr<Data> data) {
                Output(data.release());
            }

            virtual void Mflo(unique_ptr<Data> data) {
                Output(data.release());
            }

            virtual void Mthi(unique_ptr<Data> data) {
                Output(data.release());
            }

            virtual void Mtlo(unique_ptr<Data> data) {
                Output(data.release());
            }

            virtual void Mult(unique_ptr<Data> data) {
                uint64_t result = static_cast<uint64_t>(static_cast<int64_t>(rs->get()) * static_cast<int64_t>(rt->get()));
                data->arithmetic_result_front = static_cast<uint32_t>(result >> 32);
                data->arithmetic_result_back = static_cast<uint32_t>(result);
                Output(data.release());
            }

            virtual void Multu(unique_ptr<Data> data) {
                uint64_t result = static_cast<uint64_t>(rs->get()) * static_cast<uint64_t>(rt->get());
                data->arithmetic_result_front = static_cast<uint32_t>(result >> 32);
                data->arithmetic_result_back = static_cast<uint32_t>(result);
                Output(data.release());
            }

            virtual void Nor(unique_ptr<Data> data) {
                data->arithmetic_result_front = ~(rs->get() | rt->get());
            }

            virtual void Or(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() | rt->get();
            }

            virtual void Sll(unique_ptr<Data> data) {
                data->arithmetic_result_front = rt->get() << instruction->shift();
                Output(data.release());
            }

            virtual void Sllv(unique_ptr<Data> data) {
                data->arithmetic_result_front = rt->get() << rs->get();
                Output(data.release());
            }

            virtual void Slt(unique_ptr<Data> data) {
                data->arithmetic_result_front = static_cast<int32_t>(rs->get()) < static_cast<int32_t>(rt->get()) ? 1 : 0;
                Output(data.release());
            }

            virtual void Sltu(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() < rt->get() ? 1 : 0;
                Output(data.release());
            }

            virtual void Sra(unique_ptr<Data> data) {
                data->arithmetic_result_front = ArithmeticShiftRight(rt->get(), instruction->shift());
                Output(data.release());
            }

            virtual void Srav(unique_ptr<Data> data) {
                data->arithmetic_result_front = ArithmeticShiftRight(rt->get(), rs->get());
                Output(data.release());
            }

            virtual void Srl(unique_ptr<Data> data) {
                data->arithmetic_result_front = rt->get() >> instruction->shift();
                Output(data.release());
            }

            virtual void Srlv(unique_ptr<Data> data) {
                data->arithmetic_result_front = rt->get() >> rs->get();
                Output(data.release());
            }

            virtual void Sub(unique_ptr<Data> data) {
                int32_t left = static_cast<int32_t>(rs->get());
                int32_t right = static_cast<int32_t>(rt->get());
                int32_t result = left - right;
                data->arithmetic_result_front = static_cast<uint32_t>(result);
                if((left < 0 && right > 0 && result > 0) || (left > 0 && right < 0 && result < 0)) {
                    controller_.Interrupt(interrupts::ArithmeticOverflowException());
                } else {
                    Output(data.release());
                }
            }

            virtual void Subu(unique_ptr<Data> data) {
                data->arithmetic_result_front = rs->get() - rt->get();
                Output(data.release());
            }

            virtual void Syscall(unique_ptr<Data> data) {
                controller_.Interrupt(interrupts::SyscallException());
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
        protected:
            virtual void Addi(unique_ptr<Data> data);
            virtual void Addiu(unique_ptr<Data> data);
            virtual void Andi(unique_ptr<Data> data);
            virtual void Beq(unique_ptr<Data> data);
            virtual void Bgez(unique_ptr<Data> data);
            virtual void Bgtz(unique_ptr<Data> data);
            virtual void Blez(unique_ptr<Data> data);
            virtual void Bltz(unique_ptr<Data> data);
            virtual void Bne(unique_ptr<Data> data);
            virtual void Lb(unique_ptr<Data> data);
            virtual void Lbu(unique_ptr<Data> data);
            virtual void Lh(unique_ptr<Data> data);
            virtual void Lhu(unique_ptr<Data> data);
            virtual void Lui(unique_ptr<Data> data);
            virtual void Lw(unique_ptr<Data> data);
            virtual void Lwc1(unique_ptr<Data> data);
            virtual void Ori(unique_ptr<Data> data);
            virtual void Sb(unique_ptr<Data> data);
            virtual void Slti(unique_ptr<Data> data);
            virtual void Sltiu(unique_ptr<Data> data);
            virtual void Sh(unique_ptr<Data> data);
            virtual void Sw(unique_ptr<Data> data);
            virtual void Swc1(unique_ptr<Data> data);
            virtual void Xori(unique_ptr<Data> data);
    };

    class Execute::Execute_J_OpcodeSwitch : public OpcodeSwitch_J_InstructionBase {
        protected:
            virtual void J(unique_ptr<Data> data);
            virtual void Jal(unique_ptr<Data> data);
    };

} // namespace exec_cycle 
