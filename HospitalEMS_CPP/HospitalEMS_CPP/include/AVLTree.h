#pragma once
#include "Patient.h"
#include <vector>
#include <memory>

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(const Patient& patient);
    Patient* search(int id);
    bool remove(int id);
    void inorder(std::vector<Patient*>& result);
    int size() const;
    int height() const;
    bool empty() const;

private:
    struct Node {
        Patient patient;
        Node* left;
        Node* right;
        int h;
        explicit Node(const Patient& p) : patient(p), left(nullptr), right(nullptr), h(1) {}
    };

    Node* root;
    int count;

    int nodeHeight(Node* n) const;
    int balanceFactor(Node* n) const;
    void updateHeight(Node* n);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* n);
    Node* insert(Node* node, const Patient& patient);
    Node* minNode(Node* node) const;
    Node* remove(Node* node, int id);
    Node* search(Node* node, int id) const;
    void inorder(Node* node, std::vector<Patient*>& result);
    void destroy(Node* node);
};
