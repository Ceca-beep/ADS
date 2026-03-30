#pragma once
#include <iostream>
#include <vector>
#include <optional>
#include <string>

template <typename T, int DEG = 3>
class BTree {
    static_assert(DEG >= 2, "Minimum degree t must be >= 2");

public:
    BTree();
    ~BTree();

    void insert(const T& key);

    bool search(const T& key) const;

    bool remove(const T& key);


    bool     empty()  const { return root_ == nullptr || root_->n == 0; }
    int      height() const;
    int      size()   const;          // total number of keys in the tree
    void     print()  const;          // level-order
    void     clear();

    BTree(const BTree&)            = delete;
    BTree& operator=(const BTree&) = delete;
    BTree(BTree&&)                 = default;
    BTree& operator=(BTree&&)      = default;

private:

    struct Node {
        int  n;
        bool leaf;
        std::vector<T>     keys;
        std::vector<Node*> children;

        explicit Node(bool is_leaf)
            : n(0), leaf(is_leaf)
        {
            keys.reserve(2 * DEG - 1);
            children.reserve(2 * DEG);
        }
    };

    Node* root_;

    void splitChild(Node* x, int i);

    void insertNonfull(Node* x, const T& key);

    Node* searchNode(Node* x, const T& key, int& idx) const;


    bool  deleteKey(Node* x, const T& key);
    T     getPredecessor(Node* x);
    T     getSuccessor(Node* x);
    void  merge(Node* x, int i);
    void  fillChild(Node* x, int i);
    void  borrowFromPrev(Node* x, int i);
    void  borrowFromNext(Node* x, int i);

    void  destroyTree(Node* x);
    int   heightOf(Node* x) const;
    int   countKeys(Node* x) const;
    void  printNode(Node* x, int depth) const;
};


template <typename T, int DEG>
BTree<T, DEG>::BTree() : root_(nullptr) {}

template <typename T, int DEG>
BTree<T, DEG>::~BTree() { clear(); }

template <typename T, int DEG>
void BTree<T, DEG>::clear() {
    destroyTree(root_);
    root_ = nullptr;
}

template <typename T, int DEG>
void BTree<T, DEG>::destroyTree(Node* x) {
    if (!x) return;
    for (Node* child : x->children) destroyTree(child);
    delete x;
}


template <typename T, int DEG>
int BTree<T, DEG>::height() const { return heightOf(root_); }

template <typename T, int DEG>
int BTree<T, DEG>::heightOf(Node* x) const {
    if (!x || x->n == 0) return 0;
    if (x->leaf) return 1;
    return 1 + heightOf(x->children[0]);
}

template <typename T, int DEG>
int BTree<T, DEG>::size() const { return countKeys(root_); }

template <typename T, int DEG>
int BTree<T, DEG>::countKeys(Node* x) const {
    if (!x) return 0;
    int total = x->n;
    for (Node* child : x->children) total += countKeys(child);
    return total;
}

template <typename T, int DEG>
typename BTree<T, DEG>::Node*
BTree<T, DEG>::searchNode(Node* x, const T& key, int& idx) const {
    if (!x) return nullptr;

    int i = 0;

    while (i < x->n && key > x->keys[i]) ++i;


    if (i < x->n && key == x->keys[i]) {
        idx = i;
        return x;
    }


    if (x->leaf) return nullptr;


    return searchNode(x->children[i], key, idx);
}

template <typename T, int DEG>
bool BTree<T, DEG>::search(const T& key) const {
    int idx = -1;
    return searchNode(root_, key, idx) != nullptr;
}


template <typename T, int DEG>
void BTree<T, DEG>::splitChild(Node* x, int i) {
    const int t = DEG;
    Node* y = x->children[i];
    Node* z = new Node(y->leaf);


    z->n = t - 1;


    for (int j = 0; j < t - 1; ++j)
        z->keys.push_back(y->keys[j + t]);


    if (!y->leaf)
        for (int j = 0; j < t; ++j)
            z->children.push_back(y->children[j + t]);


    T median = y->keys[t - 1];
    y->keys.resize(t - 1);
    if (!y->leaf) y->children.resize(t);
    y->n = t - 1;


    x->children.insert(x->children.begin() + i + 1, z);


    x->keys.insert(x->keys.begin() + i, median);


    ++x->n;


}


template <typename T, int DEG>
void BTree<T, DEG>::insert(const T& key) {

    if (!root_) {
        root_ = new Node(true);
        root_->keys.push_back(key);
        root_->n = 1;
        return;
    }


    if (root_->n == 2 * DEG - 1) {
        Node* s = new Node(false);
        s->children.push_back(root_);
        root_ = s;

        splitChild(s, 0);
        insertNonfull(s, key);
    } else {
        insertNonfull(root_, key);    // line 10
    }
}


template <typename T, int DEG>
void BTree<T, DEG>::insertNonfull(Node* x, const T& key) {
    int i = x->n - 1;
    if (x->leaf) {

        x->keys.push_back(x->keys.back());
        while (i >= 0 && key < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            --i;
        }
        x->keys[i + 1] = key;
        ++x->n;

    } else {

        while (i >= 0 && key < x->keys[i]) --i;
        ++i;


        if (x->children[i]->n == 2 * DEG - 1) {
            splitChild(x, i);
            if (key > x->keys[i]) ++i;
        }
        insertNonfull(x->children[i], key);
    }
}



template <typename T, int DEG>
T BTree<T, DEG>::getPredecessor(Node* x) {
    while (!x->leaf) x = x->children[x->n];
    return x->keys[x->n - 1];
}


template <typename T, int DEG>
T BTree<T, DEG>::getSuccessor(Node* x) {
    while (!x->leaf) x = x->children[0];
    return x->keys[0];
}


template <typename T, int DEG>
void BTree<T, DEG>::merge(Node* x, int i) {
    Node* y = x->children[i];       // left child
    Node* z = x->children[i + 1];   // right child


    y->keys.push_back(x->keys[i]);


    for (int j = 0; j < z->n; ++j)
        y->keys.push_back(z->keys[j]);


    if (!y->leaf)
        for (int j = 0; j <= z->n; ++j)
            y->children.push_back(z->children[j]);

    y->n = 2 * DEG - 1;


    x->keys.erase(x->keys.begin() + i);
    x->children.erase(x->children.begin() + i + 1);
    --x->n;

    delete z;
}


template <typename T, int DEG>
void BTree<T, DEG>::borrowFromPrev(Node* x, int i) {
    Node* child = x->children[i];
    Node* sibling = x->children[i - 1];

    child->keys.insert(child->keys.begin(), x->keys[i - 1]);
    ++child->n;

    if (!child->leaf) {
        child->children.insert(child->children.begin(),
                                sibling->children.back());
        sibling->children.pop_back();
    }

    x->keys[i - 1] = sibling->keys.back();
    sibling->keys.pop_back();
    --sibling->n;
}

template <typename T, int DEG>
void BTree<T, DEG>::borrowFromNext(Node* x, int i) {
    Node* child = x->children[i];
    Node* sibling = x->children[i + 1];

    child->keys.push_back(x->keys[i]);
    ++child->n;


    if (!child->leaf) {
        child->children.push_back(sibling->children.front());
        sibling->children.erase(sibling->children.begin());
    }

    x->keys[i] = sibling->keys.front();
    sibling->keys.erase(sibling->keys.begin());
    --sibling->n;
}


template <typename T, int DEG>
void BTree<T, DEG>::fillChild(Node* x, int i) {
    const bool hasLeftSib  = (i > 0)          && (x->children[i - 1]->n >= DEG);
    const bool hasRightSib = (i < x->n)       && (x->children[i + 1]->n >= DEG);

    if (hasLeftSib) {
        borrowFromPrev(x, i);
    } else if (hasRightSib) {
        borrowFromNext(x, i);
    } else {

        if (i < x->n)
            merge(x, i);
        else
            merge(x, i - 1);
    }
}


template <typename T, int DEG>
bool BTree<T, DEG>::deleteKey(Node* x, const T& key) {
    int i = 0;

    while (i < x->n && key > x->keys[i]) ++i;

    if (i < x->n && x->keys[i] == key) {


        if (x->leaf) {

            x->keys.erase(x->keys.begin() + i);
            --x->n;
            return true;
        }


        Node* y = x->children[i];
        Node* z = x->children[i + 1];

        if (y->n >= DEG) {

            T pred = getPredecessor(y);
            x->keys[i] = pred;
            return deleteKey(y, pred);
        }

        if (z->n >= DEG) {

            T succ = getSuccessor(z);
            x->keys[i] = succ;
            return deleteKey(z, succ);
        }


        merge(x, i);
        return deleteKey(y, key);

    } else {


        if (x->leaf) return false;


        bool lastChild = (i == x->n);


        if (x->children[i]->n < DEG) {
            fillChild(x, i);

            if (lastChild && i > x->n) --i;
        }

        return deleteKey(x->children[i], key);
    }
}

template <typename T, int DEG>
bool BTree<T, DEG>::remove(const T& key) {
    if (!root_) return false;

    bool found = deleteKey(root_, key);


    if (root_->n == 0) {
        Node* old = root_;
        root_ = root_->leaf ? nullptr : root_->children[0];
        old->children.clear();
        delete old;
    }

    return found;
}



template <typename T, int DEG>
void BTree<T, DEG>::printNode(Node* x, int depth) const {
    if (!x) return;
    std::string indent(depth * 4, ' ');
    std::cout << indent << "[";
    for (int i = 0; i < x->n; ++i) {
        if (i > 0) std::cout << " | ";
        std::cout << x->keys[i];
    }
    std::cout << "]" << (x->leaf ? " (leaf)" : "") << "\n";
    for (Node* child : x->children) printNode(child, depth + 1);
}

template <typename T, int DEG>
void BTree<T, DEG>::print() const {
    if (!root_ || root_->n == 0) {
        std::cout << "(empty tree)\n";
        return;
    }
    std::cout << "B-Tree  t=" << DEG
              << "  keys=" << size()
              << "  height=" << height() << "\n";
    printNode(root_, 0);
}