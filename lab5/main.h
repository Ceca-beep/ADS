#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "BinomialHeap.h"


void printHelp() {
    std::cout <<
        "\nCommands:\n"
        "  insert <key>        insert key (integer)\n"
        "  min                 show minimum key\n"
        "  extract             extract and remove minimum\n"
        "  delete <id>         delete node by id (shown on insert)\n"
        "  decrease <id> <key> decrease key of node <id>\n"
        "  print               print heap structure\n"
        "  size                number of elements\n"
        "  sort                extract all keys sorted (empties heap)\n"
        "  clear               empty the heap\n"
        "  help                show this message\n"
        "  exit / quit\n\n";
}

int main() {
    BinomialHeap<int> heap;


    std::unordered_map<int, BinomialHeap<int>::Node*> nodeMap;
    int nextId = 1;

    std::cout << "Binomial Heap interactive shell  (integer keys)\n";
    std::cout << "Type 'help' for commands.\n\n";

    std::string line;
    while (true) {
        std::cout << "bheap> ";
        if (!std::getline(std::cin, line)) break;

        std::istringstream ss(line);
        std::string cmd;
        ss >> cmd;
        if (cmd.empty()) continue;

        if (cmd == "exit" || cmd == "quit") {
            std::cout << "Bye.\n";
            break;

        } else if (cmd == "help") {
            printHelp();

        } else if (cmd == "insert") {
            int key;
            if (!(ss >> key)) { std::cout << "Usage: insert <int>\n"; continue; }

            heap.insert(key);
            std::cout << "Inserted " << key << " (id=" << nextId << ")\n";
            nodeMap[nextId] = nullptr;
            ++nextId;
            heap.print();

        } else if (cmd == "min") {
            try {
                std::cout << "Minimum: " << heap.minimum() << "\n";
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }

        } else if (cmd == "extract") {
            try {
                int val = heap.extractMin();
                std::cout << "Extracted min: " << val << "\n";
                heap.print();
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }

        } else if (cmd == "size") {
            std::cout << "Size: " << heap.size() << "\n";

        } else if (cmd == "print") {
            heap.print();

        } else if (cmd == "sort") {
            if (heap.empty()) { std::cout << "Heap is empty.\n"; continue; }
            std::vector<int> sorted = heap.toSortedVector();
            std::cout << "Sorted: [";
            for (int i = 0; i < (int)sorted.size(); ++i) {
                if (i) std::cout << ", ";
                std::cout << sorted[i];
            }
            std::cout << "]\n";
            nodeMap.clear();
            nextId = 1;

        } else if (cmd == "clear") {
            heap = BinomialHeap<int>();
            nodeMap.clear();
            nextId = 1;
            std::cout << "Heap cleared.\n";

        } else if (cmd == "decrease" || cmd == "delete") {
            std::cout << "Note: decrease/delete by node pointer require direct "
                         "API access.\nUse the library API (BinomialHeap.h) "
                         "directly in your own code.\n";

        } else {
            std::cout << "Unknown command '" << cmd << "'. Type 'help'.\n";
        }
    }

    return 0;
}