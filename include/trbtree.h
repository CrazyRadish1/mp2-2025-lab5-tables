#ifndef TRBTREE_H
#define TRBTREE_H

#include <stdexcept>
#include <string>

enum NodeColor { RED, BLACK };

template <typename Key, typename Value>
class TRBTree
{
private:
    struct Node
    {
        Key key;
        Value value;
        NodeColor color;
        Node* left;
        Node* right;
        Node* parent;

        Node(const Key& k, const Value& v)
        {
            key = k;
            value = v;
            color = RED;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }

        Node()
        {
            color = BLACK;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }
    };

    Node* root;
    Node* nil;
    int opCount;

    void rotateLeft(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nil) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nil) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* x)
    {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nil) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nil) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node* z)
    {
        while (z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                Node* y = z->parent->parent->right;
                if (y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(z->parent->parent);
                }
            }
            else
            {
                Node* y = z->parent->parent->left;
                if (y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(Node* u, Node* v)
    {
        if (u->parent == nil) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        v->parent = u->parent;
    }

    Node* minimum(Node* x)
    {
        while (x->left != nil) x = x->left;
        return x;
    }

    void fixRemove(Node* x)
    {
        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                Node* w = x->parent->right;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == BLACK)
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = root;
                }
            }
            else
            {
                Node* w = x->parent->left;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == BLACK)
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    Node* findNode(const Key& key)
    {
        Node* curr = root;
        while (curr != nil)
        {
            opCount++;
            if (key == curr->key) return curr;
            else if (key < curr->key) curr = curr->left;
            else curr = curr->right;
        }
        return nullptr;
    }

    void clear(Node* node)
    {
        if (node == nil) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    TRBTree()
    {
        opCount = 0;
        nil = new Node();
        nil->left = nil;
        nil->right = nil;
        nil->parent = nil;
        root = nil;
    }

    ~TRBTree()
    {
        clear(root);
        delete nil;
    }

    void insert(const Key& key, const Value& val)
    {
        opCount = 0;
        Node* z = new Node(key, val);
        z->left = nil;
        z->right = nil;
        z->parent = nil;

        Node* y = nil;
        Node* x = root;
        while (x != nil)
        {
            y = x;
            opCount++;
            if (z->key == x->key)
            {
                delete z;
                throw std::runtime_error("Key already exists: " + key);
            }
            else if (z->key < x->key) x = x->left;
            else x = x->right;
        }

        z->parent = y;
        if (y == nil) root = z;
        else if (z->key < y->key) y->left = z;
        else y->right = z;

        fixInsert(z);
    }

    Value* find(const Key& key)
    {
        opCount = 0;
        Node* node = findNode(key);
        if (node == nullptr) return nullptr;
        return &node->value;
    }

    void remove(const Key& key)
    {
        opCount = 0;
        Node* z = findNode(key);
        if (z == nullptr)
            throw std::runtime_error("Key not found: " + key);

        Node* y = z;
        Node* x;
        NodeColor yOrigColor = y->color;

        if (z->left == nil)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nil)
        {
            x = z->left;
            transplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            yOrigColor = y->color;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (yOrigColor == BLACK)
            fixRemove(x);
    }

    int getOpCount() const { return opCount; }
};

#endif
