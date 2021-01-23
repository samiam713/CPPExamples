#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"
#include <stdlib.h>
#include <time.h>

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));

    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');

//     AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');

    return 0;
}

//#define AMOUNT 1000

//int main() {
//
//    srand((int)time(nullptr));
//    for (int j = 0; j < 10; j++) {
//
//
//    AVLTree<int, string>* tree = new AVLTree<int, string>();
//
//    int toAdd[AMOUNT];
//
//    for (int i = 0; i < AMOUNT; i++) {
//        toAdd[i] = 100 + rand() % 900;
//    }
//
//    for (int const thing : toAdd) {
//        tree->insert(make_pair(thing, to_string(thing)));
//        if (!tree->isBalanced()) {
//            cout << "FATAL ERROR" << endl;
//        }
//    }
//
//    for (int i = 0; i < AMOUNT; i++) {
//        swap(toAdd[i], toAdd[rand() % AMOUNT]);
//    }
//
//    for (int const thing : toAdd) {
//        tree->remove(thing);
//        if (!tree->isBalanced()) {
//            cout << "FATAL ERROR" << endl;
//        }
//    }
//
//    delete tree;
//    }
//    return 0;
//}
