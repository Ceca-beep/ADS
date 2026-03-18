#ifndef LEADERBOARD_H
#define LEADERBOARD_H

/*
 * Problem 1 — Dynamic Leaderboard
 *
 * Strategy:
 *   - One RBTree sorted by SCORE (the key).
 *   - A map<string, RBNode*> maps each player name to their tree node so
 *     UPDATE and REMOVE can locate the node in O(1) and delete it in O(log n).
 *   - Because two players can have the same score the tree allows duplicate keys
 *     (equal keys always go right in RBInsert, so every node is in the tree).
 *   - TOP k does a reverse-inorder traversal (right → root → left), which visits
 *     nodes in descending score order; we stop after k nodes.
 *
 * All operations are O(log n) except TOP k which is O(k log n).
 */

#include <iostream>
#include <string>
#include <map>
#include "Rbnode.h"


// We need to store a player name alongside each score.
// The simplest way without changing RBNode is a parallel map: node* -> name.
// We use TWO maps:
//   playerToNode : player name  -> RBNode* (find node by player)
//   nodeToPlayer : RBNode*      -> player name (find name during TOP k)

class Leaderboard {
private:
    RBTree tree;
    std::map<std::string, RBNode*> playerToNode;
    std::map<RBNode*, std::string> nodeToPlayer;

    // Reverse-inorder traversal: collects up to k nodes in descending key order
    void collectTopK(RBNode* node, int k, int& count) {
        if (tree.isNil(node) || count >= k) return;
        collectTopK(node->right, k, count);
        if (count < k) {
            std::cout << nodeToPlayer[node] << " " << node->key << "\n";
            count++;
            collectTopK(node->left, k, count);
        }
    }

public:
    // ADD player score
    void add(const std::string& player, int score) {
        RBNode* node = tree.createNode(score);
        tree.RBInsert(node);
        playerToNode[player] = node;
        nodeToPlayer[node]   = player;
    }

    // UPDATE player delta  (score += delta, can be negative)
    void update(const std::string& player, int delta) {
        if (playerToNode.find(player) == playerToNode.end()) {
            std::cout << "Leaderboard: Player not found: " << player << "\n";
            return;
        }
        RBNode* old = playerToNode[player];
        int newScore = old->key + delta;

        // Remove old node from both maps before deleting it
        nodeToPlayer.erase(old);
        tree.del(old);   // old is now freed — do not use it after this line

        // Insert fresh node with updated score
        RBNode* fresh = tree.createNode(newScore);
        tree.RBInsert(fresh);
        playerToNode[player] = fresh;
        nodeToPlayer[fresh]  = player;
    }

    // REMOVE player
    void remove(const std::string& player) {
        if (playerToNode.find(player) == playerToNode.end()) {
            std::cout << "Leaderboard: Player not found: " << player << "\n";
            return;
        }
        RBNode* node = playerToNode[player];
        nodeToPlayer.erase(node);
        playerToNode.erase(player);
        tree.del(node);
    }

    // TOP k — print k players with highest scores in descending order
    void top(int k) {
        int count = 0;
        collectTopK(tree.root, k, count);
        if (count == 0) std::cout << "Leaderboard: No players.\n";
    }
};

#endif