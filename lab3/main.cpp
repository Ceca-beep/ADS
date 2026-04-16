#include <iostream>
#include <cstdlib>
#include <list>
#include "Rbnode.h"
#include "IODialog.h"
#include "Leaderboard.h"
#include "DynamicMedian.h"

void perform(RBTree*, int);
void startProcessing(RBTree*);
void runLeaderboard();
void runDynamicMedian();

int main() {
    RBTree* RB = new RBTree();
    startProcessing(RB);
    delete RB;
    return 0;
}

void startProcessing(RBTree* RB) {
    int o;
    while (true) {
        o = IODialog::getTreeOperation();
        perform(RB, o);
    }
}

void perform(RBTree* RB, int o) {
    std::list<int> nodeKeys;
    RBNode* rbn;
    int skey;
    switch (o) {
    case 1:
        IODialog::getNodeKeys(nodeKeys);
        for (int k : nodeKeys) RB->RBInsert(RB->createNode(k));
        break;
    case 2:
        skey = IODialog::getNodeKey();
        rbn = RB->search(RB->root, skey);
        if (!RB->isNil(rbn)) RB->del(rbn);
        else std::cout << "RB: Node not found" << std::endl;
        break;
    case 3:
        rbn = RB->minimum(RB->root);
        if (RB->isNil(rbn)) std::cout << "RB: Minimum not found" << std::endl;
        else std::cout << "RB: Minimum is: " << rbn->toString() << std::endl;
        break;
    case 4:
        rbn = RB->maximum(RB->root);
        if (RB->isNil(rbn)) std::cout << "RB: Maximum not found" << std::endl;
        else std::cout << "RB: Maximum is: " << rbn->toString() << std::endl;
        break;
    case 5:
        skey = IODialog::getNodeKey();
        rbn = RB->search(RB->root, skey);
        if (!RB->isNil(rbn)) {
            rbn = RB->successor(rbn);
            if (RB->isNil(rbn)) std::cout << "RB: No successor.\n";
            else std::cout << "RB: Successor is: " << rbn->toString() << std::endl;
        } else std::cout << "RB: Node not found.\n";
        break;
    case 6:
        skey = IODialog::getNodeKey();
        rbn = RB->search(RB->root, skey);
        if (!RB->isNil(rbn)) {
            rbn = RB->predecessor(rbn);
            if (RB->isNil(rbn)) std::cout << "RB: No predecessor.\n";
            else std::cout << "RB: Predecessor is: " << rbn->toString() << std::endl;
        } else std::cout << "RB: Node not found.\n";
        break;
    case 7:
        RB->indentedDisplay(RB->root, 0);
        break;
    case 8:
        std::cout << "Inorder: "; RB->inorder(RB->root); std::cout << std::endl;
        break;
    case 9:
        std::cout << "Black-height: " << RB->bh() << std::endl;
        break;
    case 10:
        std::cout << "Max Black key: " << RB->maxBlackKey() << std::endl;
        break;
    case 11:
        std::cout << "Max Red key: " << RB->maxRedKey() << std::endl;
        break;
    case 12:
        std::cout << "Tree depth: " << RB->depth(RB->root) << std::endl;
        break;
    case 13:
        std::cout << "Bye!" << std::endl;
        exit(0);

    // ── NEW: Problem 1 ────────────────────────────────────────────
    case 14:
        runLeaderboard();
        break;

    // ── NEW: Problem 2 ────────────────────────────────────────────
    case 15:
        runDynamicMedian();
        break;

    default:
        std::cout << "Unknown option.\n";
    }
}

// ─────────────────────────────────────────────────────────────────
//  Problem 1 — Leaderboard sub-menu
// ─────────────────────────────────────────────────────────────────
void runLeaderboard() {
    Leaderboard lb;
    std::string player;
    int score, delta, k, op;

    std::cout << "\n=== Dynamic Leaderboard ===\n";
    while (true) {
        op = IODialog::getLeaderboardOperation();
        switch (op) {
        case 1:  // ADD
            IODialog::getPlayerScore(player, score);
            lb.add(player, score);
            break;
        case 2:  // UPDATE
            IODialog::getPlayerDelta(player, delta);
            lb.update(player, delta);
            break;
        case 3:  // REMOVE
            player = IODialog::getPlayerName();
            lb.remove(player);
            break;
        case 4:  // TOP k
            k = IODialog::getK();
            lb.top(k);
            break;
        case 5:  // Back
            return;
        default:
            std::cout << "  Unknown option.\n";
        }
    }
}

// ─────────────────────────────────────────────────────────────────
//  Problem 2 — Dynamic Median sub-menu
// ─────────────────────────────────────────────────────────────────
void runDynamicMedian() {
    DynamicMedian dm;
    int x, op;

    std::cout << "\n=== Dynamic Median ===\n";
    while (true) {
        op = IODialog::getMedianOperation();
        switch (op) {
        case 1:  // ADD
            x = IODialog::getInteger();
            dm.add(x);
            break;
        case 2:  // REMOVE
            x = IODialog::getInteger();
            dm.remove(x);
            break;
        case 3:  // MEDIAN
            dm.median();
            break;
        case 4:  // Back
            return;
        default:
            std::cout << "  Unknown option.\n";
        }
    }
}