#ifndef TADAPTERS_H
#define TADAPTERS_H

#include "itable.h"
#include "tunsortedtable.h"
#include "tsortedtable.h"
#include "trbtree.h"
#include "thashtable.h"

template <typename Key, typename Value>
class TUnsortedTableAdapter : public ITable<Key, Value>
{
private:
    TUnsortedTable<Key, Value> table;
public:
    void insert(const Key& key, const Value& val)
    {
        table.insert(key, val);
    }

    Value* find(const Key& key)
    {
        return table.find(key);
    }

    void remove(const Key& key)
    {
        table.remove(key);
    }

    int getOpCount() const { return table.getOpCount(); }
    std::string getName() const { return "UnsortedTable"; }
};

template <typename Key, typename Value>
class TSortedTableAdapter : public ITable<Key, Value>
{
private:
    TSortedTable<Key, Value> table;
public:
    void insert(const Key& key, const Value& val)
    {
        table.insert(key, val);
    }

    Value* find(const Key& key)
    {
        return table.find(key);
    }

    void remove(const Key& key)
    {
        table.remove(key);
    }

    int getOpCount() const { return table.getOpCount(); }
    std::string getName() const { return "SortedTable"; }
};

template <typename Key, typename Value>
class TRBTreeAdapter : public ITable<Key, Value>
{
private:
    TRBTree<Key, Value> table;
public:
    void insert(const Key& key, const Value& val)
    {
        table.insert(key, val);
    }

    Value* find(const Key& key)
    {
        return table.find(key);
    }

    void remove(const Key& key)
    {
        table.remove(key);
    }

    int getOpCount() const { return table.getOpCount(); }
    std::string getName() const { return "RBTree"; }
};

template <typename Key, typename Value>
class THashTableAdapter : public ITable<Key, Value>
{
private:
    THashTable<Key, Value> table;
public:
    void insert(const Key& key, const Value& val)
    {
        table.insert(key, val);
    }

    Value* find(const Key& key)
    {
        return table.find(key);
    }

    void remove(const Key& key)
    {
        table.remove(key);
    }

    int getOpCount() const { return table.getOpCount(); }
    std::string getName() const { return "HashTable"; }
};

#endif
