#include "physical_memory.h"

#include <gtest/gtest.h>

namespace {
    class PhysicalMemoryTest : public ::testing::Test {
        protected:
            virtual void SetUp() {}
            virtual void TearDown() {}

            memory::PhysicalMemory memory;
    };

    TEST_F(PhysicalMemoryTest, IsValid) {
        EXPECT_TRUE(memory.IsValid(0x00000000));
        EXPECT_TRUE(memory.IsValid(0x0000ffff));
        EXPECT_TRUE(memory.IsValid(0x0001ffff));
        EXPECT_FALSE(memory.IsValid(0x00020000));
    }

    TEST_F(PhysicalMemoryTest, setAndget) {
        memory.set(0x00000000, 0);
        EXPECT_EQ(0, memory.get(0x00000000));
        memory.set(0x00000001, 2);
        EXPECT_EQ(0, memory.get(0x00000000));
        EXPECT_EQ(2, memory.get(0x00000001));
    }
} // namespace
