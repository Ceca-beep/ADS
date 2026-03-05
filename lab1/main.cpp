#include <iostream>
#include <algorithm>

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int key) {
        if (node == nullptr) return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        return node;
    }

    Node* findMinNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* remove(Node* node, int key) {
        if (node == nullptr) return node;

        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {

            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }


            Node* temp = findMinNode(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
        return node;
    }

    bool search(Node* node, int key) {
        if (node == nullptr) return false;
        if (node->key == key) return true;
        return (key < node->key) ? search(node->left, key) : search(node->right, key);
    }

    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        std::cout << node->key << " ";
        inorder(node->right);
    }


    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:

    BST() : root(nullptr) {}


    ~BST() {
        clear(root);
        std::cout << "\n[System] Memory cleared: Tree destroyed." << std::endl;
    }


    void insert(int key) { root = insert(root, key); }
    void remove(int key) { root = remove(root, key); }
    bool search(int key) { return search(root, key); }

    void printInorder() {
        std::cout << "Tree (Inorder): ";
        inorder(root);
        std::cout << std::endl;
    }

    int getMin() {
        Node* res = findMinNode(root);
        return res ? res->key : -1;
    }

    int getMax() {
        Node* current = root;
        while (current && current->right) current = current->right;
        return current ? current->key : -1;
    }
};

int main() {
    BST tree;


    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);

    std::cout << "BST Created." << std::endl;
    std::cout << "Min value: " << tree.getMin() << std::endl; // Should be 20
    std::cout << "Max value: " << tree.getMax() << std::endl; // Should be 70
    tree.printInorder();


    if (tree.search(30)) {
        std::cout << "Found 30 in the tree!" << std::endl;
    }


    std::cout << "Deleting 30" << std::endl;
    tree.remove(30);

    if (!tree.search(30)) {
        std::cout << "30 is no longer in the tree." << std::endl;
    }

    return 0;
}