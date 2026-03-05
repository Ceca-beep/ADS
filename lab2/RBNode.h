#ifndef RBNODE_H
#define RBNODE_H

#include <iostream>
#include <string>
#include <algorithm>
#include <list>

using namespace std;

enum Color { RED, BLACK };

struct RBNode {
    int key;
    Color color;
    RBNode *left, *right, *parent;
    RBNode(int k) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    string toString() { return to_string(key) + (color == RED ? "(R)" : "(B)"); }
};

class RBTree {
public:
    RBNode *root;
    RBNode *nil;

    RBTree() {
        nil = new RBNode(0);
        nil->color = BLACK;
        root = nil;
    }

    bool isNil(RBNode* x) { return x == nil; }

    RBNode* createNode(int key) {
        RBNode* n = new RBNode(key);
        n->left = n->right = n->parent = nil;
        return n;
    }

    void leftRotate(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        if (y->left != nil) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(RBNode* y) {
        RBNode* x = y->left;
        y->left = x->right;
        if (x->right != nil) x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr) root = x;
        else if (y == y->parent->right) y->parent->right = x;
        else y->parent->left = x;
        x->right = y;
        y->parent = x;
    }

    void RBInsert(RBNode* z) {
        RBNode* y = nullptr;
        RBNode* x = root;
        while (x != nil) {
            y = x;
            if (z->key < x->key) x = x->left;
            else x = x->right;
        }
        z->parent = y;
        if (y == nullptr) root = z;
        else if (z->key < y->key) y->left = z;
        else y->right = z;
        z->left = z->right = nil;
        insertFixup(z);
    }

    void insertFixup(RBNode* k) {
        while (k->parent && k->parent->color == RED) {
            if (k->parent == k->parent->parent->left) {
                RBNode* u = k->parent->parent->right;
                if (u->color == RED) {
                    u->color = BLACK; k->parent->color = BLACK;
                    k->parent->parent->color = RED; k = k->parent->parent;
                } else {
                    if (k == k->parent->right) { k = k->parent; leftRotate(k); }
                    k->parent->color = BLACK; k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            } else {
                RBNode* u = k->parent->parent->left;
                if (u->color == RED) {
                    u->color = BLACK; k->parent->color = BLACK;
                    k->parent->parent->color = RED; k = k->parent->parent;
                } else {
                    if (k == k->parent->left) { k = k->parent; rightRotate(k); }
                    k->parent->color = BLACK; k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    RBNode* search(RBNode* x, int k) {
        if (x == nil || k == x->key) return x;
        return (k < x->key) ? search(x->left, k) : search(x->right, k);
    }

    RBNode* minimum(RBNode* x) {
        while (x != nil && x->left != nil) x = x->left;
        return x;
    }

    RBNode* maximum(RBNode* x) {
        while (x != nil && x->right != nil) x = x->right;
        return x;
    }

    RBNode* successor(RBNode* x) {
        if (x->right != nil) return minimum(x->right);
        RBNode* y = x->parent;
        while (y != nullptr && x == y->right) { x = y; y = y->parent; }
        return (y == nullptr) ? nil : y;
    }

    RBNode* predecessor(RBNode* x) {
        if (x->left != nil) return maximum(x->left);
        RBNode* y = x->parent;
        while (y != nullptr && x == y->left) { x = y; y = y->parent; }
        return (y == nullptr) ? nil : y;
    }

    int bh() {
        int h = 0;
        RBNode* curr = root;
        while (curr != nil) { if (curr->color == BLACK) h++; curr = curr->left; }
        return h;
    }

    int depth(RBNode* n) {
        if (n == nil) return 0;
        return 1 + max(depth(n->left), depth(n->right));
    }

    int maxBlackKey() { int m = -1; findMax(root, BLACK, m); return m; }
    int maxRedKey() { int m = -1; findMax(root, RED, m); return m; }
    void findMax(RBNode* n, Color c, int& m) {
        if (n == nil) return;
        if (n->color == c) m = max(m, n->key);
        findMax(n->left, c, m); findMax(n->right, c, m);
    }

    void indentedDisplay(RBNode* n, int s) {
        if (n == nil) return;
        indentedDisplay(n->right, s + 7);
        cout << string(s, ' ') << n->key << (n->color == RED ? "R" : "B") << endl;
        indentedDisplay(n->left, s + 7);
    }

    void inorder(RBNode* n) {
        if (n == nil) return;
        inorder(n->left); cout << n->key << " "; inorder(n->right);
    }

    void del(RBNode* z) {  }
};

#endif