#ifndef TTABLEMANAGER_H
#define TTABLEMANAGER_H

#include "tadapters.h"
#include "tpolinom.h"
#include <iostream>
#include <string>

class TTableManager
{
private:
    TUnsortedTableAdapter<std::string, TPolinom> unsorted;
    TSortedTableAdapter<std::string, TPolinom> sorted;
    TRBTreeAdapter<std::string, TPolinom> rbtree;
    THashTableAdapter<std::string, TPolinom> hashtable;

    ITable<std::string, TPolinom>* tables[4];

    void logOperation(const std::string& op, const std::string& key)
    {
        std::cout << "\n[" << op << "] key = \"" << key << "\"" << std::endl;
        for (int i = 0; i < 4; i++)
            std::cout << "  " << tables[i]->getName() << ": "
                      << tables[i]->getOpCount() << " ops" << std::endl;
    }

public:
    TTableManager()
    {
        tables[0] = &unsorted;
        tables[1] = &sorted;
        tables[2] = &rbtree;
        tables[3] = &hashtable;
    }

    void insert(const std::string& key, const TPolinom& val)
    {
        for (int i = 0; i < 4; i++)
            tables[i]->insert(key, val);
        logOperation("INSERT", key);
    }

    TPolinom* find(const std::string& key)
    {
        TPolinom* result = nullptr;
        for (int i = 0; i < 4; i++)
        {
            TPolinom* p = tables[i]->find(key);
            if (result == nullptr && p != nullptr)
                result = p;
        }
        logOperation("FIND", key);
        return result;
    }

    void remove(const std::string& key)
    {
        for (int i = 0; i < 4; i++)
            tables[i]->remove(key);
        logOperation("REMOVE", key);
    }
};

#endif
