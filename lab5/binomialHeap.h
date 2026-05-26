#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
class BinomialHeap {
public:
    struct Node {
        T       key;
        int     degree;
        Node*   parent;
        Node*   child;
        Node*   sibling;

        explicit Node(const T& k)
            : key(k), degree(0),
              parent(nullptr), child(nullptr), sibling(nullptr) {}
    };

    BinomialHeap() : head_(nullptr), size_(0) {}

    ~BinomialHeap() { destroyList(head_); }

    BinomialHeap(const BinomialHeap&)            = delete;
    BinomialHeap& operator=(const BinomialHeap&) = delete;

    BinomialHeap(BinomialHeap&& other) noexcept
        : head_(other.head_), size_(other.size_)
    { other.head_ = nullptr; other.size_ = 0; }

    BinomialHeap& operator=(BinomialHeap&& other) noexcept {
        if (this != &other) {
            destroyList(head_);
            head_ = other.head_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    bool empty() const { return head_ == nullptr; }
    int  size()  const { return size_; }

    void insert(const T& key) {
        BinomialHeap tmp;
        tmp.head_ = new Node(key);
        tmp.size_ = 1;
        unionWith(tmp);
    }

    const T& minimum() const {
        if (!head_) throw std::underflow_error("Heap is empty");
        return findMin()->key;
    }

    T extractMin() {
        if (!head_) throw std::underflow_error("Heap is empty");

        Node* prevMin = nullptr;
        Node* minNode = nullptr;
        Node* prev    = nullptr;
        Node* curr    = head_;

        while (curr) {
            if (!minNode || curr->key < minNode->key) {
                minNode = curr;
                prevMin = prev;
            }
            prev = curr;
            curr = curr->sibling;
        }

        T result = minNode->key;

        if (prevMin)
            prevMin->sibling = minNode->sibling;
        else
            head_ = minNode->sibling;

        BinomialHeap childHeap;
        Node* child = minNode->child;
        Node* reversedHead = nullptr;
        while (child) {
            Node* next     = child->sibling;
            child->parent  = nullptr;
            child->sibling = reversedHead;
            reversedHead   = child;
            child          = next;
        }
        childHeap.head_ = reversedHead;
        childHeap.size_ = 0;

        delete minNode;
        --size_;

        unionWith(childHeap);

        return result;
    }

    void unionWith(BinomialHeap& other) {
        head_ = mergeRootLists(head_, other.head_);
        size_ += other.size_;
        other.head_ = nullptr;
        other.size_ = 0;

        if (!head_) return;

        Node* prev = nullptr;
        Node* curr = head_;
        Node* next = curr->sibling;

        while (next) {
            if (curr->degree != next->degree ||
                (next->sibling && next->sibling->degree == curr->degree))
            {
                prev = curr;
                curr = next;
            } else {
                if (curr->key <= next->key) {
                    curr->sibling = next->sibling;
                    linkTrees(next, curr);
                } else {
                    if (prev)
                        prev->sibling = next;
                    else
                        head_ = next;
                    linkTrees(curr, next);
                    curr = next;
                }
            }
            next = curr->sibling;
        }
    }

    void decreaseKey(Node* x, const T& new_key) {
        if (new_key > x->key)
            throw std::invalid_argument("New key is greater than current key");
        x->key = new_key;
        bubbleUp(x);
    }

    void deleteNode(Node* x) {
        Node* curr = x;
        while (curr->parent) {
            std::swap(curr->key, curr->parent->key);
            curr = curr->parent;
        }

        Node* prev = nullptr;
        Node* node = head_;
        while (node && node != curr) {
            prev = node;
            node = node->sibling;
        }

        if (prev) prev->sibling = curr->sibling;
        else      head_ = curr->sibling;

        BinomialHeap childHeap;
        Node* child = curr->child;
        Node* reversedHead = nullptr;
        while (child) {
            Node* nxt      = child->sibling;
            child->parent  = nullptr;
            child->sibling = reversedHead;
            reversedHead   = child;
            child          = nxt;
        }
        childHeap.head_ = reversedHead;
        childHeap.size_ = 0;

        delete curr;
        --size_;

        unionWith(childHeap);
    }

    void print() const {
        if (!head_) { std::cout << "(empty heap)\n"; return; }
        std::cout << "Binomial Heap  n=" << size_ << "\n";
        Node* curr = head_;
        while (curr) {
            std::cout << "  B_" << curr->degree
                      << " (root key=" << curr->key << "):\n";
            printTree(curr, "    ", true);
            curr = curr->sibling;
        }
    }

    std::vector<T> toSortedVector() {
        std::vector<T> result;
        result.reserve(size_);
        while (!empty()) result.push_back(extractMin());
        return result;
    }

private:
    Node* head_;
    int   size_;

    static void linkTrees(Node* y, Node* z) {
        y->parent  = z;
        y->sibling = z->child;
        z->child   = y;
        ++z->degree;
    }

    static Node* mergeRootLists(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        Node* head = nullptr;
        Node* tail = nullptr;

        while (h1 && h2) {
            Node* chosen;
            if (h1->degree <= h2->degree) {
                chosen = h1;
                h1 = h1->sibling;
            } else {
                chosen = h2;
                h2 = h2->sibling;
            }
            if (!head) { head = tail = chosen; }
            else       { tail->sibling = chosen; tail = chosen; }
        }

        if (tail) tail->sibling = h1 ? h1 : h2;
        else      head = h1 ? h1 : h2;

        return head;
    }

    Node* findMin() const {
        Node* minNode = head_;
        Node* curr    = head_->sibling;
        while (curr) {
            if (curr->key < minNode->key) minNode = curr;
            curr = curr->sibling;
        }
        return minNode;
    }

    static void bubbleUp(Node* x) {
        while (x->parent && x->key < x->parent->key) {
            std::swap(x->key, x->parent->key);
            x = x->parent;
        }
    }

    static void destroyList(Node* node) {
        while (node) {
            destroyTree(node->child);
            Node* next = node->sibling;
            delete node;
            node = next;
        }
    }

    static void destroyTree(Node* node) {
        if (!node) return;
        destroyTree(node->child);
        destroyTree(node->sibling);
        delete node;
    }

    static void printTree(Node* node, const std::string& prefix, bool isRoot) {
        if (!node) return;
        if (isRoot)
            std::cout << prefix << node->key << "\n";
        else
            std::cout << prefix << "+-- " << node->key << "\n";
        Node* child = node->child;
        while (child) {
            printTree(child, prefix + (isRoot ? "" : "|   "), false);
            child = child->sibling;
        }
    }
};