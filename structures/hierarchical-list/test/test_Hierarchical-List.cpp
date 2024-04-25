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


TEST(HierarchicalListTest, CreateListWithInitialElements) {
    int initialValues[] = { 10, 20, 30 };
    HierarchicalList<int> list(initialValues, 3);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 3);

    int index = 0;
    int expectedValues[] = { 30, 20, 10 };
    for (auto it = list.begin(); it != list.end(); ++it, ++index) {
        EXPECT_EQ(*it, expectedValues[index]);
    }
}



TEST(HierarchicalListTest, InsertionOnLevel) {
    HierarchicalList<int> myList;
    int value1 = 1;
    int value2 = 2;
    int value3 = 3;
    myList.insertAtHorizon(value1);
    myList.insertAtHorizon(value2);
    myList.insertAtHorizon(value3);

    ASSERT_EQ(myList.size(), 3);

    int expectedValues[] = { 3, 2, 1 };
    size_t index = 0;
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        EXPECT_EQ(*it, expectedValues[index++]);
    }
}

TEST(HierarchicalListTest, InsertionAtDepth) {
    HierarchicalList<int> myList;

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;

    myList.insertAtHorizon(value1);
    myList.insertAtHorizon(value2);
    myList.insertAtHorizon(value3);

    auto it = myList.begin();
    HierarchicalList<int>::spNode firstNode = it.getNode();
    int value10 = 10;
    myList.insertAtDepth(value10, firstNode); 
    int value20 = 20;
    myList.insertAtDepth(value20, firstNode);
    int value30 = 30;
    myList.insertAtDepth(value30, firstNode); 

    ASSERT_EQ(myList.size(), 6);

    int expectedValues[] = { 30, 20, 10 };
    size_t index = 0;
    auto depthIt = firstNode->Down;
    while (depthIt) {
        EXPECT_EQ(depthIt->Value, expectedValues[index++]);
        depthIt = depthIt->Next;
    }
}

TEST(HierarchicalListTest, Find) {
    HierarchicalList<int> myList;

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;

    myList.insertAtHorizon(value1);
    myList.insertAtHorizon(value2);
    myList.insertAtHorizon(value3);

    auto it = myList.begin();
    HierarchicalList<int>::spNode firstNode = it.getNode();
    int value10 = 10;
    myList.insertAtDepth(value10, firstNode);
    int value20 = 20;
    myList.insertAtDepth(value20, firstNode);
    int value30 = 30;
    myList.insertAtDepth(value30, firstNode);

    ASSERT_EQ(myList.size(), 6);

    EXPECT_EQ(*myList.find(value20), 20);
    EXPECT_EQ(*myList.find(value30), 30);
}

TEST(HierarchicalListTest, RemoveElement) {
    HierarchicalList<int> myList;

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;

    myList.insertAtHorizon(value1);
    myList.insertAtHorizon(value2);
    myList.insertAtHorizon(value3);

    auto it = myList.begin();
    HierarchicalList<int>::spNode firstNode = it.getNode();
    int value10 = 10;
    myList.insertAtDepth(value10, firstNode);
    int value20 = 20;
    myList.insertAtDepth(value20, firstNode);
    int value30 = 30;
    myList.insertAtDepth(value30, firstNode);

    ASSERT_EQ(myList.size(), 6);

    myList.remove(value2);
    EXPECT_EQ(myList.size(), 5);
    myList.remove(value20);
    EXPECT_EQ(myList.size(), 3);

}







