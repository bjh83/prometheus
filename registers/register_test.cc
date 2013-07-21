#include "register.h"

#include <gtest/gtest.h>

namespace {
    using registers::Register;
    using registers::GetRegister;

    TEST(RegisterTest, GetRegister_byNumber) {
        Register& reg = GetRegister(0);
        EXPECT_EQ(0, reg.get());
        Register& reg1 = GetRegister(1);
        reg1.set(55);
        EXPECT_EQ(55, registers::at);
        Register& reg2 = GetRegister(31);
        reg2.set(111);
        EXPECT_EQ(111, registers::ra);
    }

} // namespace
