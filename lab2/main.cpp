#include <iostream>
#include <cstdlib>
#include <list>
#include "RBNode.h"
#include "IODialog.h"

using namespace std;

void perform(RBTree*, int);
void startProcessing(RBTree*);

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
    list<int> nodeKeys;
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
       else cout << "RB: Node not found" << endl;
       break;
    case 3:
       rbn = RB->minimum(RB->root);
       if (RB->isNil(rbn)) cout << "RB: Minimum not found" << endl;
       else cout << "RB: Minimum is: " << rbn->toString() << endl;
       break;
    case 4:
       rbn = RB->maximum(RB->root);
       if (RB->isNil(rbn)) cout << "RB: Maximum not found" << endl;
       else cout << "RB: Maximum is: " << rbn->toString() << endl;
       break;
    case 5:
       skey = IODialog::getNodeKey();
       rbn = RB->search(RB->root, skey);
       if (!RB->isNil(rbn)) {
          rbn = RB->successor(rbn);
          if (RB->isNil(rbn)) cout << "RB: No successor.\n";
          else cout << "RB: Successor is: " << rbn->toString() << endl;
       } else cout << "RB: Node not found.\n";
       break;
    case 6:
       skey = IODialog::getNodeKey();
       rbn = RB->search(RB->root, skey);
       if (!RB->isNil(rbn)) {
          rbn = RB->predecessor(rbn);
          if (RB->isNil(rbn)) cout << "RB: No predecessor.\n";
          else cout << "RB: Predecessor is: " << rbn->toString() << endl;
       } else cout << "RB: Node not found.\n";
       break;
    case 7:
       RB->indentedDisplay(RB->root, 0);
       break;
    case 8:
       cout << "Inorder: "; RB->inorder(RB->root); cout << endl;
       break;
    case 9:
       cout << "Black-height: " << RB->bh() << endl;
       break;
    case 10:
       cout << "Max Black key: " << RB->maxBlackKey() << endl;
       break;
    case 11:
       cout << "Max Red key: " << RB->maxRedKey() << endl;
       break;
    case 12:
       cout << "Tree depth: " << RB->depth(RB->root) << endl;
       break;
    case 13:
       cout << "Bye!" << endl;
       exit(0);
    }
}