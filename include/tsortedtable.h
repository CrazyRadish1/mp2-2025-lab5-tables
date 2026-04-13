#ifndef TSORTEDTABLE_H
#define TSORTEDTABLE_H

#include "tvector.h"
#include <stdexcept>
#include <string>

template <typename Key, typename Value>
class TSortedTable
{
private:
    struct Record
    {
        Key key;
        Value value;
    };

    TVector<Record> data;
    int opCount;

public:
    TSortedTable()
    {
        opCount = 0;
    }

    void insert(const Key& key, const Value& val)
    {
        opCount = 0;
        int lo = 0, hi = data.getSize() - 1;
        int pos = data.getSize();
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            opCount++;
            if (data[mid].key == key)
                throw std::runtime_error("Key already exists: " + key);
            else if (data[mid].key < key)
                lo = mid + 1;
            else
            {
                pos = mid;
                hi = mid - 1;
            }
        }
        Record rec;
        rec.key = key;
        rec.value = val;
        data.insert(pos, rec);
    }

    Value* find(const Key& key)
    {
        opCount = 0;
        int lo = 0, hi = data.getSize() - 1;
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            opCount++;
            if (data[mid].key == key)
                return &data[mid].value;
            else if (data[mid].key < key)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return nullptr;
    }

    void remove(const Key& key)
    {
        opCount = 0;
        int lo = 0, hi = data.getSize() - 1, pos = -1;
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            opCount++;
            if (data[mid].key == key)
            {
                pos = mid;
                break;
            }
            else if (data[mid].key < key)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        if (pos == -1)
            throw std::runtime_error("Key not found: " + key);
        data.erase(pos);
    }

    int getOpCount() const { return opCount; }
};

#endif
