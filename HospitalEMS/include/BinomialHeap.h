#pragma once
#include "Patient.h"
#include <vector>

class BinomialHeap {
public:
    BinomialHeap();
    ~BinomialHeap();

    void insert(const Patient& patient);
    Patient* peekMin();
    Patient extractMin();
    int size() const;
    bool empty() const;
    std::vector<Patient> toSortedList() const;

private:
    struct Node {
        Patient patient;
        int degree;
        Node* child;
        Node* sibling;
        Node* parent;
        explicit Node(const Patient& p)
            : patient(p), degree(0), child(nullptr), sibling(nullptr), parent(nullptr) {}
    };

    Node* head;
    int count;

    Node* linkTrees(Node* y, Node* z);
    Node* mergeHeaps(Node* h1, Node* h2);
    Node* consolidate(Node* h);
    Node* reverseList(Node* node);
    void collectAll(Node* node, std::vector<Patient>& out) const;
    void destroy(Node* node);
};
