#ifndef THEADLIST_H
#define THEADLIST_H

template <class T>
struct TNode
{
    T val;
    TNode<T>* pNext;
};

template <class T>
class THeadList
{
protected:
    TNode<T>* pHead;
    int len;

public:
    THeadList()
    {
        pHead = new TNode<T>;
        pHead->pNext = pHead;
        len = 0;
    }

    THeadList(const THeadList& other)
    {
        pHead = new TNode<T>;
        pHead->pNext = pHead;
        len = 0;
        TNode<T>* curr = other.pHead->pNext;
        while (curr != other.pHead)
        {
            InsLast(curr->val);
            curr = curr->pNext;
        }
    }

    THeadList& operator=(const THeadList& other)
    {
        if (this == &other) return *this;
        while (pHead->pNext != pHead) DelFirst();
        TNode<T>* curr = other.pHead->pNext;
        while (curr != other.pHead)
        {
            InsLast(curr->val);
            curr = curr->pNext;
        }
        return *this;
    }

    ~THeadList()
    {
        TNode<T>* temp = pHead->pNext;
        while (temp != pHead)
        {
            TNode<T>* next = temp->pNext;
            delete temp;
            temp = next;
        }
        delete pHead;
        pHead = nullptr;
    }

    void InsLast(const T& val)
    {
        TNode<T>* curr = pHead;
        while (curr->pNext != pHead)
            curr = curr->pNext;
        TNode<T>* newNode = new TNode<T>;
        newNode->val = val;
        newNode->pNext = pHead;
        curr->pNext = newNode;
        len++;
    }

    void InsOrdered(const T& val)
    {
        TNode<T>* prev = pHead;
        TNode<T>* curr = pHead->pNext;
        while (curr != pHead && curr->val > val)
        {
            prev = curr;
            curr = curr->pNext;
        }
        TNode<T>* newNode = new TNode<T>;
        newNode->val = val;
        newNode->pNext = curr;
        prev->pNext = newNode;
        len++;
    }

    void InsertAfter(TNode<T>* prev, const T& val)
    {
        TNode<T>* newNode = new TNode<T>;
        newNode->val = val;
        newNode->pNext = prev->pNext;
        prev->pNext = newNode;
        len++;
    }

    void DeleteAfter(TNode<T>* prev)
    {
        TNode<T>* toDelete = prev->pNext;
        prev->pNext = toDelete->pNext;
        delete toDelete;
        len--;
    }

    void DelFirst()
    {
        if (pHead->pNext == pHead) return;
        TNode<T>* temp = pHead->pNext;
        pHead->pNext = temp->pNext;
        delete temp;
        len--;
    }

    int GetLength() const { return len; }
    TNode<T>* GetHead() const { return pHead; }
};

#endif
