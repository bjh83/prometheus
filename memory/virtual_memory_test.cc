#include "virtual_memory.h"

#include <gtest/gtest.h>
#include "prometheus/utils/utils.h"

namespace {
    class VirtualMemoryTest : public ::testing::Test {
        protected:
            // virtual void SetUp() {}
            // virtual void TearDown() {}

            memory::VirtualMemory memory_;
    };

    TEST_F(VirtualMemoryTest, IsValid) {
        EXPECT_TRUE(memory_.IsValid(0x80000000));
        EXPECT_TRUE(memory_.IsValid(0x8001ffff));
        EXPECT_TRUE(memory_.IsValid(0x8000ffff));
        EXPECT_FALSE(memory_.IsValid(0x80020000));
        EXPECT_FALSE(memory_.IsValid(0x00000000));
    }

    TEST_F(VirtualMemoryTest, setAndget) {
        memory_.set(0x80000000, 0x00000000);
        EXPECT_EQ(0x00000000, memory_.get_uint8(0x80000000));
        EXPECT_EQ(0x00000000, memory_.get_uint8(0x80000001));
        EXPECT_EQ(0x00000000, memory_.get_uint8(0x80000002));
        EXPECT_EQ(0x00000000, memory_.get_uint8(0x80000003));
        memory_.set(0x80000000, 0x01);
        EXPECT_EQ(0x01, memory_.get_uint8(0x80000000));
        EXPECT_EQ(0x00, memory_.get_uint8(0x80000001));
        EXPECT_EQ(0x01000000, memory_.get_uint32(0x00000000));
    }

} // namespace
