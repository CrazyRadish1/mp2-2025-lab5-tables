#include "../include/ttablemanager.h"
#include <gtest.h>
#include <stdexcept>

using namespace std;

TPolinom makePoly(double c, int ind)
{
    TPolinom p;
    TMonom m = { c, ind };
    p.AddMonom(m);
    return p;
}

TEST(TUnsortedTable, can_insert_and_find)
{
    TUnsortedTable<string, TPolinom> t;
    t.insert("p1", makePoly(3.0, 100));
    EXPECT_NE(nullptr, t.find("p1"));
}

TEST(TUnsortedTable, find_returns_correct_value)
{
    TUnsortedTable<string, TPolinom> t;
    t.insert("p1", makePoly(3.0, 100));
    TPolinom* p = t.find("p1");
    ASSERT_NE(nullptr, p);
    EXPECT_DOUBLE_EQ(3.0, p->GetHead()->pNext->val.coeff);
}

TEST(TUnsortedTable, find_missing_returns_null)
{
    TUnsortedTable<string, TPolinom> t;
    EXPECT_EQ(nullptr, t.find("missing"));
}

TEST(TUnsortedTable, duplicate_key_throws)
{
    TUnsortedTable<string, TPolinom> t;
    t.insert("p1", makePoly(1.0, 100));
    EXPECT_THROW(t.insert("p1", makePoly(2.0, 200)), runtime_error);
}

TEST(TUnsortedTable, can_remove)
{
    TUnsortedTable<string, TPolinom> t;
    t.insert("p1", makePoly(1.0, 100));
    t.remove("p1");
    EXPECT_EQ(nullptr, t.find("p1"));
}

TEST(TUnsortedTable, remove_missing_throws)
{
    TUnsortedTable<string, TPolinom> t;
    EXPECT_THROW(t.remove("missing"), runtime_error);
}

TEST(TUnsortedTable, opcounter_works)
{
    TUnsortedTable<string, TPolinom> t;
    t.insert("a", makePoly(1.0, 100));
    t.insert("b", makePoly(2.0, 200));
    t.find("b");
    EXPECT_EQ(2, t.getOpCount());
}

TEST(TSortedTable, can_insert_and_find)
{
    TSortedTable<string, TPolinom> t;
    t.insert("p1", makePoly(3.0, 100));
    EXPECT_NE(nullptr, t.find("p1"));
}

TEST(TSortedTable, find_returns_correct_value)
{
    TSortedTable<string, TPolinom> t;
    t.insert("p1", makePoly(5.0, 200));
    TPolinom* p = t.find("p1");
    ASSERT_NE(nullptr, p);
    EXPECT_DOUBLE_EQ(5.0, p->GetHead()->pNext->val.coeff);
}

TEST(TSortedTable, find_missing_returns_null)
{
    TSortedTable<string, TPolinom> t;
    EXPECT_EQ(nullptr, t.find("missing"));
}

TEST(TSortedTable, duplicate_key_throws)
{
    TSortedTable<string, TPolinom> t;
    t.insert("p1", makePoly(1.0, 100));
    EXPECT_THROW(t.insert("p1", makePoly(2.0, 200)), runtime_error);
}

TEST(TSortedTable, maintains_sorted_order)
{
    TSortedTable<string, TPolinom> t;
    t.insert("c", makePoly(1.0, 100));
    t.insert("a", makePoly(2.0, 200));
    t.insert("b", makePoly(3.0, 300));
    EXPECT_NE(nullptr, t.find("a"));
    EXPECT_NE(nullptr, t.find("b"));
    EXPECT_NE(nullptr, t.find("c"));
}

TEST(TSortedTable, can_remove)
{
    TSortedTable<string, TPolinom> t;
    t.insert("p1", makePoly(1.0, 100));
    t.remove("p1");
    EXPECT_EQ(nullptr, t.find("p1"));
}

TEST(TSortedTable, remove_missing_throws)
{
    TSortedTable<string, TPolinom> t;
    EXPECT_THROW(t.remove("missing"), runtime_error);
}

TEST(TRBTree, can_insert_and_find)
{
    TRBTree<string, TPolinom> t;
    t.insert("p1", makePoly(3.0, 100));
    EXPECT_NE(nullptr, t.find("p1"));
}

TEST(TRBTree, find_returns_correct_value)
{
    TRBTree<string, TPolinom> t;
    t.insert("p1", makePoly(7.0, 300));
    TPolinom* p = t.find("p1");
    ASSERT_NE(nullptr, p);
    EXPECT_DOUBLE_EQ(7.0, p->GetHead()->pNext->val.coeff);
}

TEST(TRBTree, find_missing_returns_null)
{
    TRBTree<string, TPolinom> t;
    EXPECT_EQ(nullptr, t.find("missing"));
}

TEST(TRBTree, duplicate_key_throws)
{
    TRBTree<string, TPolinom> t;
    t.insert("p1", makePoly(1.0, 100));
    EXPECT_THROW(t.insert("p1", makePoly(2.0, 200)), runtime_error);
}

TEST(TRBTree, can_insert_many)
{
    TRBTree<string, TPolinom> t;
    t.insert("d", makePoly(1.0, 100));
    t.insert("b", makePoly(2.0, 200));
    t.insert("f", makePoly(3.0, 300));
    t.insert("a", makePoly(4.0, 400));
    t.insert("c", makePoly(5.0, 500));
    EXPECT_NE(nullptr, t.find("a"));
    EXPECT_NE(nullptr, t.find("c"));
    EXPECT_NE(nullptr, t.find("f"));
}

TEST(TRBTree, can_remove)
{
    TRBTree<string, TPolinom> t;
    t.insert("p1", makePoly(1.0, 100));
    t.remove("p1");
    EXPECT_EQ(nullptr, t.find("p1"));
}

TEST(TRBTree, remove_missing_throws)
{
    TRBTree<string, TPolinom> t;
    EXPECT_THROW(t.remove("missing"), runtime_error);
}

TEST(TRBTree, opcounter_works)
{
    TRBTree<string, TPolinom> t;
    t.insert("p1", makePoly(1.0, 100));
    t.find("p1");
    EXPECT_GT(t.getOpCount(), 0);
}

TEST(THashTable, can_insert_and_find)
{
    THashTable<string, TPolinom> t;
    t.insert("p1", makePoly(3.0, 100));
    EXPECT_NE(nullptr, t.find("p1"));
}

TEST(THashTable, find_returns_correct_value)
{
    THashTable<string, TPolinom> t;
    t.insert("p1", makePoly(4.0, 100));
    TPolinom* p = t.find("p1");
    ASSERT_NE(nullptr, p);
    EXPECT_DOUBLE_EQ(4.0, p->GetHead()->pNext->val.coeff);
}

TEST(THashTable, find_missing_returns_null)
{
    THashTable<string, TPolinom> t;
    EXPECT_EQ(nullptr, t.find("missing"));
}

TEST(THashTable, duplicate_key_throws)
{
    THashTable<string, TPolinom> t;
    t.insert("p1", makePoly(1.0, 100));
    EXPECT_THROW(t.insert("p1", makePoly(2.0, 200)), runtime_error);
}

TEST(THashTable, can_remove)
{
    THashTable<string, TPolinom> t;
    t.insert("p1", makePoly(1.0, 100));
    t.remove("p1");
    EXPECT_EQ(nullptr, t.find("p1"));
}

TEST(THashTable, remove_missing_throws)
{
    THashTable<string, TPolinom> t;
    EXPECT_THROW(t.remove("missing"), runtime_error);
}

TEST(THashTable, handles_collision)
{
    THashTable<string, TPolinom> t(1);
    t.insert("p1", makePoly(1.0, 100));
    t.insert("p2", makePoly(2.0, 200));
    EXPECT_NE(nullptr, t.find("p1"));
    EXPECT_NE(nullptr, t.find("p2"));
}
