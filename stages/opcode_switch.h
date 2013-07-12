#ifndef OPCODE_SWITCH_H
#define OPCODE_SWITCH_H

#include <cstdint>
#include <memory>
#include "data.h"
#include "stage.h"

namespace exec_cycle {
    using std::unique_ptr;

    class OpcodeSwitchBase {
        public:
            OpcodeSwitchBase(Stage& stage) : stage_(stage) {}
            virtual void Switch(unique_ptr<Data> data);
        protected:
            virtual void InternalSwitch(unique_ptr<Data> data) = 0;
            virtual void Initialize(Data& data) = 0;
            Stage& stage_;
    };

    class OpcodeSwitch_R_InstructionBase : public OpcodeSwitchBase {
        protected:
            virtual void InternalSwitch(unique_ptr<Data> data);
            virtual void Add(unique_ptr<Data> data) = 0;
            virtual void Addu(unique_ptr<Data> data) = 0;
            virtual void And(unique_ptr<Data> data) = 0;
            virtual void Break(unique_ptr<Data> data) = 0;
            virtual void Div(unique_ptr<Data> data) = 0;
            virtual void Divu(unique_ptr<Data> data) = 0;
            virtual void Jalr(unique_ptr<Data> data) = 0;
            virtual void Jr(unique_ptr<Data> data) = 0;
            virtual void Mfhi(unique_ptr<Data> data) = 0;
            virtual void Mflo(unique_ptr<Data> data) = 0;
            virtual void Mthi(unique_ptr<Data> data) = 0;
            virtual void Mtlo(unique_ptr<Data> data) = 0;
            virtual void Mult(unique_ptr<Data> data) = 0;
            virtual void Multu(unique_ptr<Data> data) = 0;
            virtual void Nor(unique_ptr<Data> data) = 0;
            virtual void Or(unique_ptr<Data> data) = 0;
            virtual void Sll(unique_ptr<Data> data) = 0;
            virtual void Sllv(unique_ptr<Data> data) = 0;
            virtual void Slt(unique_ptr<Data> data) = 0;
            virtual void Sltu(unique_ptr<Data> data) = 0;
            virtual void Sra(unique_ptr<Data> data) = 0;
            virtual void Srav(unique_ptr<Data> data) = 0;
            virtual void Srl(unique_ptr<Data> data) = 0;
            virtual void Srlv(unique_ptr<Data> data) = 0;
            virtual void Sub(unique_ptr<Data> data) = 0;
            virtual void Subu(unique_ptr<Data> data) = 0;
            virtual void Syscall(unique_ptr<Data> data) = 0;
            virtual void Xor(unique_ptr<Data> data) = 0;
    };

    class OpcodeSwitch_I_InstructionBase : public OpcodeSwitchBase {
        protected:
            virtual void InternalSwitch(unique_ptr<Data> data) = 0;
            virtual void Addi(unique_ptr<Data> data) = 0;
            virtual void Addiu(unique_ptr<Data> data) = 0;
            virtual void Andi(unique_ptr<Data> data) = 0;
            virtual void Beq(unique_ptr<Data> data) = 0;
            virtual void Bgez(unique_ptr<Data> data) = 0;
            virtual void Bgtz(unique_ptr<Data> data) = 0;
            virtual void Blez(unique_ptr<Data> data) = 0;
            virtual void Bltz(unique_ptr<Data> data) = 0;
            virtual void Bne(unique_ptr<Data> data) = 0;
            virtual void Lb(unique_ptr<Data> data) = 0;
            virtual void Lbu(unique_ptr<Data> data) = 0;
            virtual void Lh(unique_ptr<Data> data) = 0;
            virtual void Lhu(unique_ptr<Data> data) = 0;
            virtual void Lui(unique_ptr<Data> data) = 0;
            virtual void Lw(unique_ptr<Data> data) = 0;
            virtual void Lwc1(unique_ptr<Data> data) = 0;
            virtual void Ori(unique_ptr<Data> data) = 0;
            virtual void Sb(unique_ptr<Data> data) = 0;
            virtual void Slti(unique_ptr<Data> data) = 0;
            virtual void Sltiu(unique_ptr<Data> data) = 0;
            virtual void Sh(unique_ptr<Data> data) = 0;
            virtual void Sw(unique_ptr<Data> data) = 0;
            virtual void Swc1(unique_ptr<Data> data) = 0;
            virtual void Xori(unique_ptr<Data> data) = 0;
    };

    class OpcodeSwitch_J_InstructionBase : public OpcodeSwitchBase {
        protected:
            virtual void InternalSwitch(unique_ptr<Data> data) = 0;
            virtual void J(unique_ptr<Data> data) = 0;
            virtual void Jal(unique_ptr<Data> data) = 0;
    };

} // namespace exec_cycle
#endif // OPCODE_SWITCH_H
