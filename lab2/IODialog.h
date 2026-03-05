#ifndef IODIALOG_H
#define IODIALOG_H

#include <iostream>
#include <list>
using namespace std;

class IODialog {
public:
    static int getTreeOperation() {
        int choice;
        cout << "\n1.Add ";
        cout << "\n2.Delete ";
        cout << "\n3.Min ";
        cout << "\n4.Max ";
        cout << "\n5.Succ ";
        cout << "\n6.Pred ";
        cout << "\n.Show ";
        cout << "\n8.Inorder ";
        cout << "\n9.BH ";
        cout << "\n10.MaxB ";
        cout << "\n11.MaxR ";
        cout << "\n12.Depth ";
        cout << "\n13.Exit";
        cout << "\nChoice: ";
        cin >> choice;
        return choice;
    }
    static void getNodeKeys(list<int>& keys) {
        int n, k;
        cout << "How many nodes? "; cin >> n;
        cout << "Enter keys: ";
        for(int i=0; i<n; i++) { cin >> k; keys.push_back(k); }
    }
    static int getNodeKey() {
        int k;
        cout << "Enter key: "; cin >> k;
        return k;
    }
};
#endif