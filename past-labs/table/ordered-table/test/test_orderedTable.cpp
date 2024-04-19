#include <gtest/gtest.h>
#include <OrderedTable.h>
using namespace std;

TEST(OrderedTableTest, Insert) {
    OrderedTable<int, string> table;
    table.Insert(1, "one");
    ASSERT_EQ(table.GetDataCount(), 1);
    ASSERT_EQ(*table.Find(1), "one");
}

TEST(OrderedTableTest, Delete) {
    OrderedTable<int, string> table;
    table.Insert(1, "one");
    table.Delete(1);
    ASSERT_EQ(table.GetDataCount(), 0);
    ASSERT_THROW(table.Find(1), std::runtime_error);
}

TEST(OrderedTableTest, IsEmpty) {
    OrderedTable<int, string> table;
    ASSERT_TRUE(table.IsEmpty());
    table.Insert(1, "one");
    ASSERT_FALSE(table.IsEmpty());
}

TEST(OrderedTableTest, IsFull) {
    OrderedTable<int, string> table(1);
    ASSERT_FALSE(table.IsFull());
    table.Insert(1, "one");
    ASSERT_TRUE(table.IsFull());
}

TEST(OrderedTableTest, Find) {
    OrderedTable<int, string> table;
    table.Insert(1, "one");
    ASSERT_EQ(*table.Find(1), "one");
    ASSERT_THROW(table.Find(2), std::runtime_error);
}

TEST(OrderedTableTest, GoNext) {
    OrderedTable<int, string> table;
    table.Insert(1, "one");
    table.Insert(2, "two");
    ASSERT_EQ(table.GoNext(), 1);
    ASSERT_EQ(table.GoNext(), 2);
    ASSERT_EQ(table.GoNext(), 0);
}

TEST(OrderedTableTest, GetKeyAndValue) {
    OrderedTable<int, string> table;
    table.Insert(1, "one");
    table.Insert(2, "two");
    ASSERT_EQ(table.GetKey(), 1);
    ASSERT_EQ(*table.GetValuePtr(), "one");
    ASSERT_EQ(table.GoNext(), 1);
    ASSERT_EQ(table.GetKey(), 2);
    ASSERT_EQ(*table.GetValuePtr(), "two");
}
