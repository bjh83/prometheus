#include "stage.h"

namespace exec_cycle {

    class MemRead::MemRead_R_OpcodeSwitch : public OpcodeSwitch_R_InstructionNoOp {};

    class MemRead::MemRead_I_OpcodeSwitch : public OpcodeSwitch_I_InstructionBase {
        protected:
            virtual void Lb(unique_ptr<Data> data);
            virtual void Lbu(unique_ptr<Data> data);
            virtual void Lh(unique_ptr<Data> data);
            virtual void Lhu(unique_ptr<Data> data);
            virtual void Lui(unique_ptr<Data> data);
            virtual void Lw(unique_ptr<Data> data);
            virtual void Lwc1(unique_ptr<Data> data);
    };

    class MemRead::MemRead_J_OpcodeSwitch : public OpcodeSwitch_J_InstructionBase {};

    MemRead::MemRead(Controller& controller) : Stage(controller), r_switch_(new MemRead_R_OpcodeSwitch(*this)),
        i_switch_(new MemRead_I_OpcodeSwitch(*this)), j_switch_(new MemRead_J_OpcodeSwitch(*this)) {}

    void MemRead::Input(unique_ptr<Data> data) {
        switch(data->decoded_instruction->GetType()) {
            case DecodedInstruction::R_Type:
                r_switch_->Switch(unique_ptr<Data>(data.release()));
                break;
            case DecodedInstruction::I_Type:
                i_switch_->Switch(unique_ptr<Data>(data.release()));
                break;
            case DecodedInstruction::J_Type:
                j_switch_->Switch(unique_ptr<Data>(data.release()));
                break;
            case DecodedInstruction::Invalid:
                utils::FatalError("Decode failed to catch invalid instruction");
                break;
        }
    }

} // namespace exec_cycle
