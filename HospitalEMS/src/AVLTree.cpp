#include "AVLTree.h"
#include <algorithm>

AVLTree::AVLTree() : root(nullptr), count(0) {}

AVLTree::~AVLTree() { destroy(root); }

void AVLTree::destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

int AVLTree::nodeHeight(Node* n) const { return n ? n->h : 0; }

int AVLTree::balanceFactor(Node* n) const {
    return n ? nodeHeight(n->left) - nodeHeight(n->right) : 0;
}

void AVLTree::updateHeight(Node* n) {
    if (n) n->h = 1 + std::max(nodeHeight(n->left), nodeHeight(n->right));
}

AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLTree::Node* AVLTree::balance(Node* n) {
    updateHeight(n);
    int bf = balanceFactor(n);
    if (bf > 1) {
        if (balanceFactor(n->left) < 0) n->left = rotateLeft(n->left);
        return rotateRight(n);
    }
    if (bf < -1) {
        if (balanceFactor(n->right) > 0) n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
    return n;
}

AVLTree::Node* AVLTree::insert(Node* node, const Patient& patient) {
    if (!node) { count++; return new Node(patient); }
    if (patient.getId() < node->patient.getId())
        node->left = insert(node->left, patient);
    else if (patient.getId() > node->patient.getId())
        node->right = insert(node->right, patient);
    else {
        node->patient = patient;
        return node;
    }
    return balance(node);
}

void AVLTree::insert(const Patient& patient) { root = insert(root, patient); }

AVLTree::Node* AVLTree::search(Node* node, int id) const {
    if (!node) return nullptr;
    if (id == node->patient.getId()) return node;
    if (id < node->patient.getId()) return search(node->left, id);
    return search(node->right, id);
}

Patient* AVLTree::search(int id) {
    Node* node = search(root, id);
    return node ? &node->patient : nullptr;
}

AVLTree::Node* AVLTree::minNode(Node* node) const {
    while (node->left) node = node->left;
    return node;
}

AVLTree::Node* AVLTree::remove(Node* node, int id) {
    if (!node) return nullptr;
    if (id < node->patient.getId())
        node->left = remove(node->left, id);
    else if (id > node->patient.getId())
        node->right = remove(node->right, id);
    else {
        if (!node->left) { Node* r = node->right; delete node; count--; return r; }
        if (!node->right) { Node* l = node->left; delete node; count--; return l; }
        Node* succ = minNode(node->right);
        node->patient = succ->patient;
        node->right = remove(node->right, succ->patient.getId());
        count++;
    }
    return balance(node);
}

bool AVLTree::remove(int id) {
    if (!search(root, id)) return false;
    root = remove(root, id);
    return true;
}

void AVLTree::inorder(Node* node, std::vector<Patient*>& result) {
    if (!node) return;
    inorder(node->left, result);
    result.push_back(&node->patient);
    inorder(node->right, result);
}

void AVLTree::inorder(std::vector<Patient*>& result) { inorder(root, result); }

int AVLTree::size() const { return count; }
int AVLTree::height() const { return nodeHeight(root); }
bool AVLTree::empty() const { return count == 0; }
