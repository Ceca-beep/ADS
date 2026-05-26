#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include "../include/BTree.h"

void printHelp() {
    std::cout <<
        "\nCommands:\n"
        "  insert <key>    B-Tree-Insert\n"
        "  search <key>    B-Tree-Search\n"
        "  delete <key>    B-Tree-Delete\n"
        "  print           pretty-print the tree\n"
        "  height          current tree height\n"
        "  size            total number of keys\n"
        "  clear           empty the tree\n"
        "  demo            run all lecture demos\n"
        "  help            show this message\n"
        "  exit / quit     exit\n\n";
}

void interactiveLoop() {
    // Default t=3 (lecture default)
    BTree<int, 3> tree;
    std::string line;

    std::cout << "B-Tree interactive shell  (t=3, integer keys)\n";
    std::cout << "Type 'commands' for commands.\n\n";

    while (true) {
        std::cout << "btree> ";
        if (!std::getline(std::cin, line)) break;

        std::istringstream ss(line);
        std::string cmd;
        ss >> cmd;
        if (cmd.empty()) continue;

        if (cmd == "exit" || cmd == "quit") {
            std::cout << "Bye.\n";
            break;
        } else if (cmd == "commands") {
            printHelp();
        } else if (cmd == "print") {
            tree.print();
        } else if (cmd == "height") {
            std::cout << "Height: " << tree.height() << "\n";
        } else if (cmd == "size") {
            std::cout << "Keys:   " << tree.size() << "\n";
        } else if (cmd == "clear") {
            tree.clear();
            std::cout << "Tree cleared.\n";
        } else if (cmd == "insert") {
            int key;
            if (!(ss >> key)) { std::cout << "Usage: insert <int>\n"; continue; }
            tree.insert(key);
            std::cout << "Inserted " << key << "\n";
            tree.print();
        } else if (cmd == "search") {
            int key;
            if (!(ss >> key)) { std::cout << "Usage: search <int>\n"; continue; }
            std::cout << (tree.search(key) ? "Found" : "Not found") << ": " << key << "\n";
        } else if (cmd == "delete") {
            int key;
            if (!(ss >> key)) { std::cout << "Usage: delete <int>\n"; continue; }
            if (tree.remove(key))
                std::cout << "Deleted " << key << "\n";
            else
                std::cout << key << " not found in tree.\n";
            tree.print();
        } else {
            std::cout << "Unknown command '" << cmd << "'. Type 'commands'.\n";
        }
    }
}

int main(int argc, char* argv[]) {
    interactiveLoop();
    return 0;
}