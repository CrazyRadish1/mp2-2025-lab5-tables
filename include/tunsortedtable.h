#ifndef TUNSORTEDTABLE_H
#define TUNSORTEDTABLE_H

#include "tvector.h"
#include <stdexcept>
#include <string>

template <typename Key, typename Value>
class TUnsortedTable
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
    TUnsortedTable()
    {
        opCount = 0;
    }

    void insert(const Key& key, const Value& val)
    {
        opCount = 0;
        for (int i = 0; i < data.getSize(); i++)
        {
            opCount++;
            if (data[i].key == key)
                throw std::runtime_error("Key already exists: " + key);
        }
        Record rec;
        rec.key = key;
        rec.value = val;
        data.pushBack(rec);
    }

    Value* find(const Key& key)
    {
        opCount = 0;
        for (int i = 0; i < data.getSize(); i++)
        {
            opCount++;
            if (data[i].key == key)
                return &data[i].value;
        }
        return nullptr;
    }

    void remove(const Key& key)
    {
        opCount = 0;
        for (int i = 0; i < data.getSize(); i++)
        {
            opCount++;
            if (data[i].key == key)
            {
                data[i] = data[data.getSize() - 1];
                data.erase(data.getSize() - 1);
                return;
            }
        }
        throw std::runtime_error("Key not found: " + key);
    }

    int getOpCount() const { return opCount; }
};

#endif
