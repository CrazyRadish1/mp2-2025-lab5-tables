#ifndef TVECTOR_H
#define TVECTOR_H

#include <stdexcept>
#include <utility>

template <typename T>
class TVector
{
private:
    T* data;
    int size;
    int capacity;

    void grow()
    {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; i++)
            newData[i] = std::move(data[i]);
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    TVector()
    {
        capacity = 8;
        size = 0;
        data = new T[capacity];
    }

    ~TVector()
    {
        delete[] data;
    }

    TVector(const TVector& other)
    {
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    TVector& operator=(const TVector& other)
    {
        if (this == &other) return *this;
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
        return *this;
    }

    TVector(TVector&& other)
    {
        data = other.data;
        size = other.size;
        capacity = other.capacity;
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    TVector& operator=(TVector&& other)
    {
        if (this == &other) return *this;
        delete[] data;
        data = other.data;
        size = other.size;
        capacity = other.capacity;
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
        return *this;
    }

    void pushBack(const T& val)
    {
        if (size >= capacity) grow();
        data[size] = val;
        size++;
    }

    void pushBack(T&& val)
    {
        if (size >= capacity) grow();
        data[size] = std::move(val);
        size++;
    }

    void insert(int idx, const T& val)
    {
        if (idx < 0 || idx > size)
            throw std::runtime_error("Index out of range");
        if (size >= capacity) grow();
        for (int i = size; i > idx; i--)
            data[i] = std::move(data[i - 1]);
        data[idx] = val;
        size++;
    }

    void erase(int idx)
    {
        if (idx < 0 || idx >= size)
            throw std::runtime_error("Index out of range");
        for (int i = idx; i < size - 1; i++)
            data[i] = std::move(data[i + 1]);
        size--;
    }

    T& operator[](int idx) { return data[idx]; }
    const T& operator[](int idx) const { return data[idx]; }

    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
};

#endif
