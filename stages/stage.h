#ifndef STAGE_H
#define STAGE_H

#include <cstdint>
#include <memory>

#include "prometheus/utils/utils.h"
#include "prometheus/registers/register.h"
#include "data.h"
#include "controller.h"
#include "interrupts/exceptions.h"

namespace exec_cycle {
    using namespace std;

    class Stage {
        public:
            virtual void Input(unique_ptr<Data> data) = 0;
            void Connect(Stage* stage);
        protected:
            void Output(Data* data) { next_stage->Input(unique_ptr<Data>(data)); };
        private:
            std::unique_ptr<Stage> next_stage;
    };

    class Fetch : public Stage {
        public:
            virtual void Input(unique_ptr<Data> data);
    };

    class Decode : public Stage {
        public:
            virtual void Input(unique_ptr<Data> data);
    };

    class Execute : public Stage {
        public:
            virtual void Input(unique_ptr<Data> data);
        private:
            void Execute_R(unique_ptr<Data> data);
            void Execute_I(unique_ptr<Data> data);
            void Execute_J(unique_ptr<Data> data);
    };

    class MemRead : public Stage {
        public:
            virtual void Input(unique_ptr<Data> data);
    };

    class MemWrite : public Stage {
        public:
            virtual void Input(unique_ptr<Data> data);
    };

    class WriteBack : public Stage {
        public:
            virtual void Input(unique_ptr<Data> data);
    };
} // namespace exec_cycle
#endif // STAGE_H
