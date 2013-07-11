#include "stage.h"

namespace exec_cycle {

    class MemRead::MemRead_R_OpcodeSwitch : public OpcodeSwitch_R_InstructionBase {
        protected:
            virtual void Add(unique_ptr<Data> data);
            virtual void Addu(unique_ptr<Data> data);
            virtual void And(unique_ptr<Data> data);
            virtual void Break(unique_ptr<Data> data);
            virtual void Div(unique_ptr<Data> data);
            virtual void Divu(unique_ptr<Data> data);
            virtual void Jalr(unique_ptr<Data> data);
            virtual void Jr(unique_ptr<Data> data);
            virtual void Mfhi(unique_ptr<Data> data);
            virtual void Mflo(unique_ptr<Data> data);
            virtual void Mthi(unique_ptr<Data> data);
            virtual void Mtlo(unique_ptr<Data> data);
            virtual void Mult(unique_ptr<Data> data);
            virtual void Multu(unique_ptr<Data> data);
            virtual void Nor(unique_ptr<Data> data);
            virtual void Or(unique_ptr<Data> data);
            virtual void Sll(unique_ptr<Data> data);
            virtual void Sllv(unique_ptr<Data> data);
            virtual void Slt(unique_ptr<Data> data);
            virtual void Sltu(unique_ptr<Data> data);
            virtual void Sra(unique_ptr<Data> data);
            virtual void Srav(unique_ptr<Data> data);
            virtual void Srl(unique_ptr<Data> data);
            virtual void Srlv(unique_ptr<Data> data);
            virtual void Sub(unique_ptr<Data> data);
            virtual void Subu(unique_ptr<Data> data);
            virtual void Syscall(unique_ptr<Data> data);
            virtual void Xor(unique_ptr<Data> data);
    };

    class MemRead::MemRead_I_OpcodeSwitch : public OpcodeSwitch_I_InstructionBase {
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

    class MemRead::MemRead_J_OpcodeSwitch : public OpcodeSwitch_J_InstructionBase {
        protected:
            virtual void J(unique_ptr<Data> data);
            virtual void Jal(unique_ptr<Data> data);
    };

} // namespace exec_cycle
