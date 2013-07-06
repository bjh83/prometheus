#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>

namespace registers {

    class Register {
        public:
            Register() {}
            ~Register() {}
            virtual uint32_t get() const { return value; }
            virtual void set(uint32_t new_value) { value = new_value; }
        private:
            uint32_t value;
    };

    class ZeroRegister : public Register {
        public:
            virtual uint32_t get() const { return 0; }
            virtual void set(uint32_t new_value) {}
    };

    enum RegisterName {
        ZERO,
        AT,
        V0,
        V1,
        A0,
        A1,
        A2,
        A3,
        T0,
        T1,
        T2,
        T3,
        T4,
        T5,
        T6,
        T7,
        S0,
        S1,
        S2,
        S3,
        S4,
        S5,
        S6,
        S7,
        T8,
        T9,
        K0,
        K1,
        GP,
        SP,
        FP,
        RA,
    };

    ZeroRegister zero;
    Register at;
    Register v0;
    Register v1;
    Register a0;
    Register a1;
    Register a2;
    Register a3;
    Register t0;
    Register t1;
    Register t2;
    Register t3;
    Register t4;
    Register t5;
    Register t6;
    Register t7;
    Register s0;
    Register s1;
    Register s2;
    Register s3;
    Register s4;
    Register s5;
    Register s6;
    Register s7;
    Register t8;
    Register t9;
    Register k0;
    Register k1;
    Register gp;
    Register sp;
    Register fp;
    Register ra;

    Register& GetRegister(RegisterName name);
    Register& GetRegister(uint32_t register_number);

} // namespace registers
#endif // REGISTER_H
