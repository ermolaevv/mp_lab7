#include <gtest/gtest.h>
#include "SkipList.h"
using namespace std;


TEST(SkipListTest, ConstructorCreatesEmptyList) {
    SkipList<int> sl(3, 0.5);  
    EXPECT_TRUE(sl.empty());
    EXPECT_EQ(sl.size(), 0);
}


TEST(SkipListTest, InsertIncreasesSize) {
    SkipList<int> sl(3, 0.5);
    int value = 5;
    sl.insert(value);
    EXPECT_EQ(sl.size(), 1);
}

TEST(SkipListTest, InsertIncreasesSize_2) {
    SkipList<int> sl(3, 0.5);
    int value1 = 5;
    int value2 = 10;
    int value3 = 7;
    sl.insert(value1);
    sl.insert(value2);
    sl.insert(value3);
    EXPECT_EQ(sl.size(), 3);
}


TEST(SkipListTest, RemoveDecreasesSize) {
    SkipList<int> sl(3, 0.5);
    int value1 = 5;
    sl.insert(value1);
    int value2 = 10;
    sl.insert(value2);
    int value3 = 110;
    sl.insert(value3);
    sl.remove(value1);
    int value4 = 120;
    sl.insert(value4);
    sl.remove(value3);
    sl.remove(value4);
    sl.remove(value2);
    EXPECT_EQ(sl.size(), 0);
}


TEST(SkipListTest, EmptyListCheck) {
    SkipList<int> sl(3, 0.5);
    EXPECT_TRUE(sl.empty());
    int value = 5;
    sl.insert(value);
    EXPECT_FALSE(sl.empty());
}


TEST(SkipListTest, ClearList) {
    SkipList<int> sl(3, 0.5);
    int value1 = 5;
    int value2 = 10;
    sl.insert(value1);
    sl.insert(value2);
    sl.clear();
    EXPECT_TRUE(sl.empty());
}


TEST(SkipListTest, DefaultConstructor) {
    SkipList<int> sl;
    EXPECT_TRUE(sl.empty());
}


TEST(SkipListTest, ParametrizedConstructor) {
    SkipList<int> sl(3, 0.5);
    EXPECT_TRUE(sl.empty());
    EXPECT_EQ(sl.size(), 0);
}


TEST(SkipListTest, CopyConstructor) {
    SkipList<int> original(3, 0.5);
    int value = 1;
    original.insert(value);
    SkipList<int> copy(original);
    EXPECT_EQ(copy.size(), 1);
}


TEST(SkipListTest, CopyAssignmentOperator) {
    SkipList<int> sl1(3, 0.5);
    int value = 1;
    sl1.insert(value);
    SkipList<int> sl2;
    sl2 = sl1;
    EXPECT_EQ(sl1.size(), sl2.size());
}




