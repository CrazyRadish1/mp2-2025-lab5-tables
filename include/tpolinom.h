#ifndef TPOLINOM_H
#define TPOLINOM_H

#include "theadlist.h"
#include <iostream>

struct TMonom
{
    double coeff;
    int ind;

    bool operator>(const TMonom& other) const { return ind > other.ind; }
    bool operator<(const TMonom& other) const { return ind < other.ind; }
    bool operator==(const TMonom& other) const { return ind == other.ind; }
    bool operator!=(const TMonom& other) const { return ind != other.ind; }
};

class TPolinom
{
private:
    THeadList<TMonom> list;

public:
    TPolinom();

    TPolinom operator+(const TPolinom& q) const;
    TPolinom operator-(const TPolinom& q) const;
    TPolinom operator*(const TPolinom& q) const;
    TPolinom operator*(double val) const;

    void AddMonom(TMonom m);

    TNode<TMonom>* GetHead() const { return list.GetHead(); }
    int GetLength() const { return list.GetLength(); }

    friend std::ostream& operator<<(std::ostream& os, const TPolinom& p);
    friend std::istream& operator>>(std::istream& is, TPolinom& p);
};

#endif
