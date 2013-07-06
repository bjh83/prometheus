#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <cstdint>

namespace interrupts {
    class Exception {
    };

    class UndefinedInstruction : public Exception {
        public:
            UndefinedInstruction(uint32_t instruction);
    };

    class SyscallException : public Exception {
        public:
            SyscallException();
    };

    class ArithmeticOverflowException : public Exception {
        public:
            ArithmeticOverflowException();
    };

    class BreakException : public Exception {
        public:
            BreakException();
    };
} // namespace interrupts
#endif // EXECPTIONS_H
