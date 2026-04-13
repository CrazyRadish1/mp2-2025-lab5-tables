#ifndef ITABLE_H
#define ITABLE_H

#include <string>

template <typename Key, typename Value>
class ITable
{
public:
    virtual ~ITable() {}

    virtual void insert(const Key& key, const Value& val) = 0;
    virtual Value* find(const Key& key) = 0;
    virtual void remove(const Key& key) = 0;

    virtual int getOpCount() const = 0;
    virtual std::string getName() const = 0;
};

#endif
