#include "tpolinom.h"
#include <cmath>
#include <stdexcept>

using namespace std;

TPolinom::TPolinom()
{
    list.GetHead()->val.ind = -1;
    list.GetHead()->val.coeff = 0.0;
}

void TPolinom::AddMonom(TMonom m)
{
    if (fabs(m.coeff) < 1e-10) return;

    TNode<TMonom>* prev = list.GetHead();
    TNode<TMonom>* curr = list.GetHead()->pNext;

    while (curr != list.GetHead() && curr->val.ind > m.ind)
    {
        prev = curr;
        curr = curr->pNext;
    }

    if (curr != list.GetHead() && curr->val.ind == m.ind)
    {
        curr->val.coeff += m.coeff;
        if (fabs(curr->val.coeff) < 1e-10)
            list.DeleteAfter(prev);
    }
    else
    {
        list.InsertAfter(prev, m);
    }
}

TPolinom TPolinom::operator*(double val) const
{
    TPolinom res;
    if (fabs(val) < 1e-10) return res;

    TNode<TMonom>* curr = list.GetHead()->pNext;
    while (curr != list.GetHead())
    {
        TMonom m = curr->val;
        m.coeff *= val;
        res.list.InsLast(m);
        curr = curr->pNext;
    }
    return res;
}

TPolinom TPolinom::operator+(const TPolinom& q) const
{
    TPolinom res;
    TNode<TMonom>* p1 = list.GetHead()->pNext;
    TNode<TMonom>* p2 = q.list.GetHead()->pNext;

    while (p1 != list.GetHead() && p2 != q.list.GetHead())
    {
        if (p1->val.ind > p2->val.ind)
        {
            res.list.InsLast(p1->val);
            p1 = p1->pNext;
        }
        else if (p1->val.ind < p2->val.ind)
        {
            res.list.InsLast(p2->val);
            p2 = p2->pNext;
        }
        else
        {
            TMonom m = p1->val;
            m.coeff += p2->val.coeff;
            if (fabs(m.coeff) > 1e-10)
                res.list.InsLast(m);
            p1 = p1->pNext;
            p2 = p2->pNext;
        }
    }
    while (p1 != list.GetHead())
    {
        res.list.InsLast(p1->val);
        p1 = p1->pNext;
    }
    while (p2 != q.list.GetHead())
    {
        res.list.InsLast(p2->val);
        p2 = p2->pNext;
    }
    return res;
}

TPolinom TPolinom::operator-(const TPolinom& q) const
{
    return (*this) + (q * -1.0);
}

TPolinom TPolinom::operator*(const TPolinom& q) const
{
    TPolinom raw;
    TNode<TMonom>* p1 = list.GetHead()->pNext;

    while (p1 != list.GetHead())
    {
        TNode<TMonom>* p2 = q.list.GetHead()->pNext;
        while (p2 != q.list.GetHead())
        {
            TMonom m;
            m.coeff = p1->val.coeff * p2->val.coeff;
            m.ind = p1->val.ind + p2->val.ind;

            int x = m.ind / 100;
            int y = (m.ind / 10) % 10;
            int z = m.ind % 10;

            if (x > 9 || y > 9 || z > 9)
                throw runtime_error("Degree too large (>9)");

            raw.list.InsOrdered(m);
            p2 = p2->pNext;
        }
        p1 = p1->pNext;
    }

    TPolinom res;
    TNode<TMonom>* curr = raw.list.GetHead()->pNext;
    while (curr != raw.list.GetHead())
    {
        res.AddMonom(curr->val);
        curr = curr->pNext;
    }
    return res;
}

ostream& operator<<(ostream& os, const TPolinom& p)
{
    TNode<TMonom>* curr = p.list.GetHead()->pNext;
    if (curr == p.list.GetHead())
    {
        os << "0";
        return os;
    }

    bool first = true;
    while (curr != p.list.GetHead())
    {
        if (!first && curr->val.coeff > 0) os << "+";
        os << curr->val.coeff;

        int x = curr->val.ind / 100;
        int y = (curr->val.ind / 10) % 10;
        int z = curr->val.ind % 10;

        if (x > 0) os << "x^" << x;
        if (y > 0) os << "y^" << y;
        if (z > 0) os << "z^" << z;

        first = false;
        curr = curr->pNext;
    }
    return os;
}

istream& operator>>(istream& is, TPolinom& p)
{
    int count;
    is >> count;
    for (int i = 0; i < count; i++)
    {
        double c;
        int ind;
        is >> c >> ind;
        TMonom m = { c, ind };
        p.AddMonom(m);
    }
    return is;
}
