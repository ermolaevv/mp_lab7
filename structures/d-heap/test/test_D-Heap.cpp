#include <gtest/gtest.h>
#include "DHeap.h"
using namespace std;

TEST(DHeapTest, DefaultConstructor) {
    DHeap<int> heap;
    EXPECT_TRUE(heap.empty());
}

TEST(DHeapTest, ConstructorWithArray) {
    int arr[] = { 1, 2, 3, 4, 5 };
    DHeap<int> heap(2, arr, 5);
    EXPECT_EQ(heap.size(), 5);
    EXPECT_EQ(heap.getMax(), 5);
}

TEST(DHeapTest, CopyConstructor) {
    int arr[] = { 1, 2, 3, 4, 5 };
    DHeap<int> heap1(2, arr, 5);
    DHeap<int> heap2(heap1);
    EXPECT_EQ(heap1.size(), heap2.size());
    EXPECT_EQ(heap1.getMax(), heap2.getMax());
}

TEST(DHeapTest, AssignmentOperator) {
    int arr[] = { 1, 2, 3, 4, 5 };
    DHeap<int> heap1(2, arr, 5);
    DHeap<int> heap2;
    heap2 = heap1;
    EXPECT_EQ(heap1.size(), heap2.size());
    EXPECT_EQ(heap1.getMax(), heap2.getMax());
}

TEST(DHeapTest, Insert) {
    DHeap<int> heap;
    int value = 1;
    heap.insert(value);
    EXPECT_EQ(heap.size(), 1);
    EXPECT_EQ(heap.getMax(), 1);
}

//TEST(DHeapTest, Remove) {
//    int arr[] = { 1, 2, 3, 4, 5 };
//    DHeap<int> heap(2, arr, 5);
//    int value = 1;
//    heap.remove(value);
//    EXPECT_EQ(heap.size(), 4);
//    EXPECT_EQ(heap.getMax(), 4);
//}

//TEST(DHeapTest, ToSortedVector) {
//    int arr[] = { 1, 2, 3, 4, 5 };
//    DHeap<int> heap(2, arr, 5);
//    std::vector<int> sortedVector = heap.toSortedVector();
//    EXPECT_EQ(sortedVector, std::vector<int>({ 5, 4, 3, 2, 1 }));
//}

TEST(DHeapTest, Find) {
    int arr[] = { 1, 2, 3, 4, 5 };
    DHeap<int> heap(2, arr, 5);
    int value = 3;
    auto it = heap.find(value);
    EXPECT_EQ(*it, 3);
}

TEST(DHeapTest, Clear) {
    int arr[] = { 1, 2, 3, 4, 5 };
    DHeap<int> heap(2, arr, 5);
    heap.clear();
    EXPECT_TRUE(heap.empty());
}
