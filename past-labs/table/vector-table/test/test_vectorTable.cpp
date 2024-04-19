#include <gtest/gtest.h>
#include "VectorTable.h"
using namespace std;


TEST(VectorTableTest, Insert) {
    VectorTable<int, string> table;
    table.Insert(1, "one");
    ASSERT_EQ(table.GetDataCount(), 1);
    ASSERT_EQ(*table.Find(1), "one");
}

TEST(VectorTableTest, Delete) {
    VectorTable<int, string> table;
    table.Insert(1, "one");
    table.Delete(1);
    ASSERT_EQ(table.GetDataCount(), 0);
    ASSERT_THROW(table.Find(1), std::runtime_error);
}

TEST(VectorTableTest, IsEmpty) {
    VectorTable<int, string> table;
    ASSERT_TRUE(table.IsEmpty());
    table.Insert(1, "one");
    ASSERT_FALSE(table.IsEmpty());
}

TEST(VectorTableTest, IsFull) {
    VectorTable<int, string> table(1);
    ASSERT_FALSE(table.IsFull());
    table.Insert(1, "one");
    ASSERT_TRUE(table.IsFull());
}

TEST(VectorTableTest, Find) {
    VectorTable<int, string> table;
    table.Insert(1, "one");
    ASSERT_EQ(*table.Find(1), "one");
    ASSERT_THROW(table.Find(2), std::runtime_error);
}

TEST(VectorTableTest, GoNext) {
    VectorTable<int, string> table;
    table.Insert(1, "one");
    table.Insert(2, "two");
    ASSERT_EQ(table.GoNext(), 1);
    ASSERT_EQ(table.GoNext(), 2);
    ASSERT_EQ(table.GoNext(), 0);
}

TEST(VectorTableTest, GetKeyAndValue) {
    VectorTable<int, string> table;
    table.Insert(1, "one");
    table.Insert(2, "two");
    ASSERT_EQ(table.GetKey(), 1);
    ASSERT_EQ(*table.GetValuePtr(), "one");
    ASSERT_EQ(table.GoNext(), 1);
    ASSERT_EQ(table.GetKey(), 2);
    ASSERT_EQ(*table.GetValuePtr(), "two");
}
