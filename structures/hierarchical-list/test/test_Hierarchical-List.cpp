#include <gtest/gtest.h>
#include "HierarchicalList.h"
using namespace std;

TEST(HierarchicalListTest, Constructor) {
    HierarchicalList<int> list;
    EXPECT_EQ(list.size(), 0);
}


TEST(HierarchicalListTest, CopyConstructor) {
    HierarchicalList<int> list1;
    HierarchicalList<int> list2(list1);
    EXPECT_EQ(list2.size(), 0);
}


TEST(HierarchicalListTest, AssignmentOperator) {
    HierarchicalList<int> list1;
    HierarchicalList<int> list2;
    list2 = list1;
    EXPECT_EQ(list2.size(), 0);
}


