#include <gtest/gtest.h>
#include "SkipList.h"
using namespace std;

TEST(SkipListTest, ConstructorCreatesEmptyList) {
    SkipList<int> sl(3, 0.5);  
    EXPECT_TRUE(sl.empty());
    EXPECT_EQ(sl.size(), 0);
}

