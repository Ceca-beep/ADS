#ifndef IODIALOG_H
#define IODIALOG_H

#include <iostream>
#include <list>
#include <string>
#include <limits>

class IODialog {
public:
    static int getTreeOperation() {
        int choice;
        while (true) {
            std::cout << "\n1.Add ";
            std::cout << "\n2.Delete ";
            std::cout << "\n3.Min ";
            std::cout << "\n4.Max ";
            std::cout << "\n5.Succ ";
            std::cout << "\n6.Pred ";
            std::cout << "\n7.Show ";
            std::cout << "\n8.Inorder ";
            std::cout << "\n9.BH ";
            std::cout << "\n10.MaxB ";
            std::cout << "\n11.MaxR ";
            std::cout << "\n12.Depth ";
            std::cout << "\n13.Exit";
            std::cout << "\n--- Problems ---";
            std::cout << "\n14.Leaderboard ";
            std::cout << "\n15.Dynamic Median ";
            std::cout << "\nChoice: ";
            std::cin >> choice;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            if (choice >= 1 && choice <= 15) return choice;
            std::cout << "Invalid choice. Please select 1-15.\n";
        }
    }

    static void getNodeKeys(std::list<int>& keys) {
        int n, k;
        std::cout << "How many nodes? "; std::cin >> n;
        if (std::cin.fail() || n < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid number of nodes.\n";
            return;
        }
        std::cout << "Enter keys: ";
        for (int i = 0; i < n; i++) {
            std::cin >> k;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid key input.\n";
                break;
            }
            keys.push_back(k);
        }
    }

    static int getNodeKey() {
        int k;
        std::cout << "Enter key: "; std::cin >> k;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid key input.\n";
            return 0;
        }
        return k;
    }

    // ── Leaderboard helpers ──────────────────────────────────────
    static int getLeaderboardOperation() {
        int choice;
        while (true) {
            std::cout << "\n  1.ADD player score";
            std::cout << "\n  2.UPDATE player delta";
            std::cout << "\n  3.REMOVE player";
            std::cout << "\n  4.TOP k";
            std::cout << "\n  5.Back";
            std::cout << "\n  Choice: ";
            std::cin >> choice;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            if (choice >= 1 && choice <= 5) return choice;
            std::cout << "Invalid choice. Please select 1-5.\n";
        }
    }

    static void getPlayerScore(std::string& player, int& score) {
        std::cout << "  Player name: "; std::cin >> player;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid player name.\n";
            return;
        }
        std::cout << "  Score: "; std::cin >> score;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid score.\n";
        }
    }

    static void getPlayerDelta(std::string& player, int& delta) {
        std::cout << "  Player name: "; std::cin >> player;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid player name.\n";
            return;
        }
        std::cout << "  Delta: "; std::cin >> delta;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid delta.\n";
        }
    }

    static std::string getPlayerName() {
        std::string name;
        std::cout << "  Player name: "; std::cin >> name;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid player name.\n";
            return "";
        }
        return name;
    }

    static int getK() {
        int k;
        std::cout << "  k: "; std::cin >> k;
        if (std::cin.fail() || k <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid k. Must be positive integer.\n";
            return 1;
        }
        return k;
    }

    // ── Median helpers ───────────────────────────────────────────
    static int getMedianOperation() {
        int choice;
        while (true) {
            std::cout << "\n  1.ADD x";
            std::cout << "\n  2.REMOVE x";
            std::cout << "\n  3.MEDIAN";
            std::cout << "\n  4.Back";
            std::cout << "\n  Choice: ";
            std::cin >> choice;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            if (choice >= 1 && choice <= 4) return choice;
            std::cout << "Invalid choice. Please select 1-4.\n";
        }
    }

    static int getInteger() {
        int x;
        std::cout << "  Value: "; std::cin >> x;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid value.\n";
            return 0;
        }
        return x;
    }
};

#endif