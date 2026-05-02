#include <gtest/gtest.h>
#include "A/index.h"
#include "B/lib.h"

TEST(IndexHeaderTest, HeaderIsCorrect) {
    EXPECT_STREQ(PROJECT_NAME, "IndustrialProg");
    EXPECT_EQ(MAGIC_COUNT, 10);
    EXPECT_EQ(MAGIC_NUMBERS[0], 1);
    EXPECT_EQ(MAGIC_NUMBERS[1], 1);
    EXPECT_EQ(MAGIC_NUMBERS[4], 5);
    EXPECT_EQ(MAGIC_NUMBERS[9], 55);
}

TEST(LibTest, LibIsCorrect) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-1, 1), 0);
    EXPECT_EQ(add(0, 0), 0);
    EXPECT_EQ(fibonacci(0), 0);
    EXPECT_EQ(fibonacci(1), 1);
    EXPECT_EQ(fibonacci(10), 55);
}
