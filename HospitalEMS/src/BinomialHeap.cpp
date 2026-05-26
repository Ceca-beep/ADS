#include "BinomialHeap.h"
#include <algorithm>
#include <stdexcept>

BinomialHeap::BinomialHeap() : head(nullptr), count(0) {}

BinomialHeap::~BinomialHeap() { destroy(head); }

void BinomialHeap::destroy(Node* node) {
    while (node) {
        destroy(node->child);
        Node* next = node->sibling;
        delete node;
        node = next;
    }
}

BinomialHeap::Node* BinomialHeap::linkTrees(Node* y, Node* z) {
    if (y->patient > z->patient) std::swap(y, z);
    z->parent = y;
    z->sibling = y->child;
    y->child = z;
    y->degree++;
    return y;
}

BinomialHeap::Node* BinomialHeap::mergeHeaps(Node* h1, Node* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    Node* head = nullptr;
    Node* tail = nullptr;

    auto append = [&](Node* n) {
        n->sibling = nullptr;
        if (!tail) { head = tail = n; }
        else { tail->sibling = n; tail = n; }
    };

    while (h1 && h2) {
        if (h1->degree <= h2->degree) { Node* next = h1->sibling; append(h1); h1 = next; }
        else                          { Node* next = h2->sibling; append(h2); h2 = next; }
    }
    while (h1) { Node* next = h1->sibling; append(h1); h1 = next; }
    while (h2) { Node* next = h2->sibling; append(h2); h2 = next; }
    return head;
}

BinomialHeap::Node* BinomialHeap::consolidate(Node* h) {
    if (!h) return nullptr;
    Node* prev = nullptr;
    Node* curr = h;
    Node* next = curr->sibling;

    while (next) {
        if (curr->degree != next->degree ||
            (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->patient < next->patient || curr->patient.getSeverity() == next->patient.getSeverity()) {
                curr->sibling = next->sibling;
                curr = linkTrees(curr, next);
            } else {
                if (!prev) h = next;
                else prev->sibling = next;
                curr = linkTrees(next, curr);
            }
        }
        next = curr->sibling;
    }
    return h;
}

BinomialHeap::Node* BinomialHeap::reverseList(Node* node) {
    Node* prev = nullptr;
    while (node) {
        node->parent = nullptr;
        Node* next = node->sibling;
        node->sibling = prev;
        prev = node;
        node = next;
    }
    return prev;
}

void BinomialHeap::insert(const Patient& patient) {
    Node* node = new Node(patient);
    head = consolidate(mergeHeaps(head, node));
    count++;
}

Patient* BinomialHeap::peekMin() {
    if (!head) return nullptr;
    Node* min = head;
    for (Node* curr = head->sibling; curr; curr = curr->sibling)
        if (curr->patient < min->patient) min = curr;
    return &min->patient;
}

Patient BinomialHeap::extractMin() {
    if (!head) throw std::runtime_error("Heap is empty");

    Node* minPrev = nullptr;
    Node* min = head;
    Node* prev = nullptr;

    for (Node* curr = head->sibling; curr; curr = curr->sibling) {
        if (curr->patient < min->patient) { min = curr; minPrev = prev; }
        prev = curr;
    }

    if (!minPrev) head = min->sibling;
    else minPrev->sibling = min->sibling;

    Node* childList = reverseList(min->child);
    head = consolidate(mergeHeaps(head, childList));
    count--;

    Patient result = min->patient;
    min->child = nullptr;
    delete min;
    return result;
}

void BinomialHeap::collectAll(Node* node, std::vector<Patient>& out) const {
    while (node) {
        out.push_back(node->patient);
        collectAll(node->child, out);
        node = node->sibling;
    }
}

std::vector<Patient> BinomialHeap::toSortedList() const {
    std::vector<Patient> result;
    collectAll(head, result);
    std::sort(result.begin(), result.end(), [](const Patient& a, const Patient& b) {
        return a < b;
    });
    return result;
}

int BinomialHeap::size() const { return count; }
bool BinomialHeap::empty() const { return count == 0; }
