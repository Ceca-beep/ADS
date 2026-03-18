#ifndef DYNAMICMEDIAN_H
#define DYNAMICMEDIAN_H

/*
 * Problem 2 — Dynamic Median
 *
 * Strategy:
 *   - One RBTree stores all inserted integers as keys.
 *   - Duplicate values are allowed (equal keys go right in RBInsert).
 *   - MEDIAN = lower median = the ceil(n/2)-th smallest element.
 *     Example: n=4 elements → median is the 2nd smallest.
 *              n=3 elements → median is the 2nd smallest.
 *   - We count total nodes with countNodes() then call kthSmallest().
 *   - Both are O(n) here because the tree has no subtree-size augmentation.
 *     (Adding a `size` field to RBNode would give O(log n), but that requires
 *      modifying the original RBNode struct given by the teacher.)
 *
 * REMOVE x:
 *   - Searches for ONE node with key == x and deletes it.
 *   - If x appears multiple times, only one occurrence is removed (correct
 *     behaviour for a multiset).
 */

#include <iostream>
#include "Rbnode.h"

class DynamicMedian {
private:
    RBTree tree;

public:
    // ADD x
    void add(int x) {
        tree.RBInsert(tree.createNode(x));
    }

    // REMOVE x — deletes ONE node with key == x
    void remove(int x) {
        RBNode* node = tree.search(tree.root, x);
        if (tree.isNil(node)) {
            std::cout << "Median: Value " << x << " not found.\n";
            return;
        }
        tree.del(node);
    }

    // MEDIAN — lower median (ceil(n/2)-th smallest, 1-based)
    void median() {
        int n = tree.countNodes(tree.root);
        if (n == 0) {
            std::cout << "Median: No elements.\n";
            return;
        }
        int medianRank = (n + 1) / 2;   // ceil(n/2): lower median for even n
        RBNode* result = tree.kthSmallest(medianRank);
        std::cout << result->key << "\n";
    }
};

#endif