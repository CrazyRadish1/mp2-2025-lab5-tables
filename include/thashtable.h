#ifndef THASHTABLE_H
#define THASHTABLE_H

#include "tvector.h"
#include <stdexcept>
#include <string>

template <typename Key, typename Value>
class THashTable
{
private:
    struct HashNode
    {
        Key key;
        Value value;
        HashNode* next;

        HashNode(const Key& k, const Value& v)
        {
            key = k;
            value = v;
            next = nullptr;
        }
    };

    TVector<HashNode*> buckets;
    int tableSize;
    int opCount;

    int hashFunc(const Key& key) const
    {
        int h = 0;
        for (int i = 0; i < (int)key.size(); i++)
            h = (h * 31 + key[i]) % tableSize;
        return h;
    }

public:
    THashTable(int sz = 101)
    {
        tableSize = sz;
        opCount = 0;
        for (int i = 0; i < tableSize; i++)
            buckets.pushBack(nullptr);
    }

    ~THashTable()
    {
        for (int i = 0; i < tableSize; i++)
        {
            HashNode* curr = buckets[i];
            while (curr != nullptr)
            {
                HashNode* next = curr->next;
                delete curr;
                curr = next;
            }
        }
    }

    void insert(const Key& key, const Value& val)
    {
        opCount = 0;
        int idx = hashFunc(key);
        HashNode* curr = buckets[idx];
        while (curr != nullptr)
        {
            opCount++;
            if (curr->key == key)
                throw std::runtime_error("Key already exists: " + key);
            curr = curr->next;
        }
        HashNode* newNode = new HashNode(key, val);
        newNode->next = buckets[idx];
        buckets[idx] = newNode;
    }

    Value* find(const Key& key)
    {
        opCount = 0;
        int idx = hashFunc(key);
        HashNode* curr = buckets[idx];
        while (curr != nullptr)
        {
            opCount++;
            if (curr->key == key)
                return &curr->value;
            curr = curr->next;
        }
        return nullptr;
    }

    void remove(const Key& key)
    {
        opCount = 0;
        int idx = hashFunc(key);
        HashNode* curr = buckets[idx];
        HashNode* prev = nullptr;
        while (curr != nullptr)
        {
            opCount++;
            if (curr->key == key)
            {
                if (prev == nullptr) buckets[idx] = curr->next;
                else prev->next = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        throw std::runtime_error("Key not found: " + key);
    }

    int getOpCount() const { return opCount; }
};

#endif
