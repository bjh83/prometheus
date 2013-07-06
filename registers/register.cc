#include "register.h"

namespace registers {

    Register& GetRegister(RegisterName name) {
        switch(name) {
            case ZERO:
                return zero;
            case AT:
                return at;
            case V0:
                return v0;
            case V1:
                return v1;
            case A0:
                return a0;
            case A1:
                return a1;
            case A2:
                return a2;
            case A3:
                return a3;
            case T0:
                return t0;
            case T1:
                return t1;
            case T2:
                return t2;
            case T3:
                return t3;
            case T4:
                return t4;
            case T5:
                return t5;
            case T6:
                return t6;
            case T7:
                return t7;
            case S0:
                return s0;
            case S1:
                return s1;
            case S2:
                return s2;
            case S3:
                return s3;
            case S4:
                return s4;
            case S5:
                return s5;
            case S6:
                return s6;
            case S7:
                return s7;
            case T8:
                return t8;
            case T9:
                return t9;
            case K0:
                return k0;
            case K1:
                return k1;
            case GP:
                return gp;
            case SP:
                return sp;
            case FP:
                return fp;
            case RA:
                return ra;
        }
    }

    Register& GetRegister(uint32_t register_number) {
        return GetRegister(static_cast<RegisterName>(register_number));
    }

} // namespace registers
