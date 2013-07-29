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
            virtual void Switch(unique_ptr<Data> data);
        protected:
            OpcodeSwitchBase(Stage& stage) : stage_(stage) {}
            virtual void InternalSwitch(unique_ptr<Data> data) = 0;
            virtual void Initialize(Data& data) = 0;
            Stage& stage_;
    };

    class OpcodeSwitch_R_InstructionBase : public OpcodeSwitchBase {
        protected:
            OpcodeSwitch_R_InstructionBase(Stage& stage) : OpcodeSwitchBase(stage) {}
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
            OpcodeSwitch_I_InstructionBase(Stage& stage) : OpcodeSwitchBase(stage) {}
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
            OpcodeSwitch_J_InstructionBase(Stage& stage) : OpcodeSwitchBase(stage) {}
            virtual void InternalSwitch(unique_ptr<Data> data) = 0;
            virtual void J(unique_ptr<Data> data) = 0;
            virtual void Jal(unique_ptr<Data> data) = 0;
    };

    class OpcodeSwitch_R_InstructionNoOp : public OpcodeSwitch_R_InstructionBase {
        protected:
            virtual void Add(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Addu(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void And(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Break(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Div(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Divu(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Jalr(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Jr(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Mfhi(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Mflo(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Mthi(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Mtlo(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Mult(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Multu(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Nor(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Or(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Sll(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Sllv(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Slt(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Sltu(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Sra(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Srav(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Srl(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Srlv(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Sub(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Subu(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Syscall(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Xor(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
    };

    class OpcodeSwitch_I_InstructionNoOp : public OpcodeSwitch_I_InstructionBase {
        protected:
            virtual void Addi(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Addiu(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Andi(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Beq(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Bgez(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Bgtz(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Blez(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Bltz(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Bne(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Lb(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Lbu(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Lh(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Lhu(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Lui(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Lw(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Lwc1(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Ori(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Sb(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Slti(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Sltiu(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Sh(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Sw(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Swc1(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Xori(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
    };

    class OpcodeSwitch_J_InstructionNoOp : public OpcodeSwitch_J_InstructionBase {
        protected:
            virtual void J(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
            virtual void Jal(unique_ptr<Data> data) { stage_.Output(unique_ptr<Data>(data.release())); }
    };

} // namespace exec_cycle
#endif // OPCODE_SWITCH_H
