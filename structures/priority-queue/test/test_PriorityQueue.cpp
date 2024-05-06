#include <gtest/gtest.h>
#include "PriorityQueue.h"
using namespace std;


TEST(PriorityQueueTest, ConstructorAndSize) {
    int arr[] = { 1, 2, 3, 4, 5 };
    PriorityQueue<int> queue(arr, 5);
    EXPECT_EQ(queue.size(), 5);
}

TEST(PriorityQueueTest, CopyConstructor) {
    int arr[] = { 1, 2, 3, 4, 5 };
    PriorityQueue<int> queue1(arr, 5);
    PriorityQueue<int> queue2(queue1);
    EXPECT_EQ(queue2.size(), 5);
}

TEST(PriorityQueueTest, AssignmentOperator) {
    int arr[] = { 1, 2, 3, 4, 5 };
    PriorityQueue<int> queue1(arr, 5);
    PriorityQueue<int> queue2;
    queue2 = queue1;
    EXPECT_EQ(queue2.size(), 5);
}

TEST(PriorityQueueTest, Empty) {
    PriorityQueue<int> queue;
    EXPECT_TRUE(queue.empty());
}

TEST(PriorityQueueTest, Clear) {
    int arr[] = { 1, 2, 3, 4, 5 };
    PriorityQueue<int> queue(arr, 5);
    queue.clear();
    EXPECT_TRUE(queue.empty());
}

TEST(PriorityQueueTest, InsertAndPop) {
    PriorityQueue<int> queue;
    int value = 1;
    queue.insert(value, 10);
    EXPECT_EQ(queue.size(), 1);
    queue.pop();
    EXPECT_TRUE(queue.empty());
}
