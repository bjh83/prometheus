#ifndef STAGE_H
#define STAGE_H

#include <cstdint>
#include <memory>

#include "prometheus/utils/utils.h"
#include "prometheus/registers/register.h"
#include "data.h"
#include "controller.h"
#include "interrupts/exceptions.h"
#include "opcode_switch.h"

namespace exec_cycle {
    using namespace std;

    class Stage {
        public:
            Stage(Controller& controller) : controller_(controller) {}
            virtual void Input(unique_ptr<Data> data) = 0;
            void Connect(Stage* stage);
        protected:
            void Output(Data* data) { next_stage->Input(unique_ptr<Data>(data)); }
            Controller& controller_;
        private:
            std::unique_ptr<Stage> next_stage;
    };

    class Fetch : public Stage {
        public:
            Fetch(Controller& controller) : Stage(controller) {}
            virtual void Input(unique_ptr<Data> data);
    };

    class Decode : public Stage {
        public:
            explicit Decode(Controller& controller) : Stage(controller) {}
            virtual void Input(unique_ptr<Data> data);
    };

    class Execute : public Stage {
        public:
            explicit Execute(Controller& controller) : Stage(controller) {}
            virtual void Input(unique_ptr<Data> data);
        private:
            void Execute_R(unique_ptr<Data> data);
            void Execute_I(unique_ptr<Data> data);
            void Execute_J(unique_ptr<Data> data);

            class Execute_R_OpcodeSwitch;

            class Execute_I_OpcodeSwitch;

            class Execute_J_OpcodeSwitch;
    };

    class MemRead : public Stage {
        public:
            explicit MemRead(Controller& controller) : Stage(controller) {}
            virtual void Input(unique_ptr<Data> data);

        private:
            class MemRead_R_OpcodeSwitch;

            class MemRead_I_OpcodeSwitch;

            class MemRead_J_OpcodeSwitch;
    };

    class MemWrite : public Stage {
        public:
            explicit MemWrite(Controller& controller) : Stage(controller) {}
            virtual void Input(unique_ptr<Data> data);

        private:
            class MemWrite_R_OpcodeSwitch;

            class MemWrite_I_OpcodeSwitch;

            class MemWrite_J_OpcodeSwitch;
    };

    class WriteBack : public Stage {
        public:
            explicit WriteBack(Controller& controller) : Stage(controller) {}
            virtual void Input(unique_ptr<Data> data);

        private:
            class WriteBack_R_OpcodeSwitch;

            class WriteBack_I_OpcodeSwitch;

            class WriteBack_J_OpcodeSwitch;
    };
} // namespace exec_cycle
#endif // STAGE_H
