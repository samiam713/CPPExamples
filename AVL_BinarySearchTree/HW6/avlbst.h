#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
 * A special kind of node for an AVL tree, which adds the balance as a data member, plus
 * other additional helper functions. You do NOT need to implement any functionality or
 * add additional data members or helper functions.
 */
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();
    
    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);
    
    
    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;
    
protected:
    char balance_;
};

/*
 -------------------------------------------------
 Begin implementations for the AVLNode class.
 -------------------------------------------------
 */

/**
 * An explicit constructor to initialize the elements by calling the base class constructor and setting
 * the color to red since every new node will be red when it is first inserted.
 */
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
Node<Key, Value>(key, value, parent), balance_(0)
{
    
}

/**
 * A destructor which does nothing.
 */
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{
    
}

/**
 * A getter for the balance of a AVLNode.
 */
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
 * A setter for the balance of a AVLNode.
 */
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
 * Adds diff to the balance of a AVLNode.
 */
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
 * An overridden function for getting the parent since a static_cast is necessary to make sure
 * that our node is a AVLNode.
 */
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
 -----------------------------------------------
 End implementations for the AVLNode class.
 -----------------------------------------------
 */


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    
    // Add helper functions here
    
    void increaseHeight(AVLNode<Key,Value>* ofThis, bool fromLeft);
    void decreaseHeight(AVLNode<Key,Value>* ofThis, bool fromLeft);
    
    void rotateRight(AVLNode<Key,Value>* const oldTop);
    void rotateLeft(AVLNode<Key, Value>* const oldTop);
    
    void increaseRebalance(AVLNode<Key, Value>* node, bool fromLeft);
    void decreaseRebalance(AVLNode<Key, Value>* node, bool fromLeft);
    
    void innerRebalanceUtil(AVLNode<Key,Value>* node, bool fromLeft);
    void outerRebalanceUtil(AVLNode<Key,Value>* node, bool fromLeft);
    void bothRebalanceUtil(AVLNode<Key, Value>* node, bool fromLeft);
    
    static bool onLeft(AVLNode<Key,Value>* checkMe) {return checkMe->getParent()->getLeft() == checkMe;}
};


template<class Key, class Value>
void AVLTree<Key, Value>::increaseHeight(AVLNode<Key,Value>* ofThis, bool fromLeft)
{
    if (fromLeft) {
        ofThis->updateBalance(-1);
    } else {
        ofThis->updateBalance(1);
    }
    switch (ofThis->getBalance()) {
        case 0:
            return;
        case 1:
            if (ofThis->getParent() != nullptr) {
                increaseHeight(ofThis->getParent(), onLeft(ofThis));
            }
            return;
        case -1:
            if (ofThis->getParent() != nullptr) {
                increaseHeight(ofThis->getParent(), onLeft(ofThis));
            }
            return;
        case -2:
            increaseRebalance(ofThis, true);
            return;
        case 2:
            increaseRebalance(ofThis, false);
            return;
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::decreaseHeight(AVLNode<Key,Value>* ofThis, bool fromLeft)
{
    if (fromLeft) {
        ofThis->updateBalance(1);
    } else {
        ofThis->updateBalance(-1);
    }
    switch (ofThis->getBalance()) {
        case 0:
            if (ofThis->getParent() != nullptr) {
                decreaseHeight(ofThis->getParent(), onLeft(ofThis));
            }
            return;
        case 1:
            return;
        case -1:
            return;
        case -2:
            decreaseRebalance(ofThis, true);
            return;
        case 2:
            decreaseRebalance(ofThis, false);
            return;
    }
}

// IF BINARYSEARCHTREE DOES NOT HAVE ORDER PROBLEMS AFTER INSERTION, THAT MEANS ROTATING (or trickling up heights?) IS THE THING SCREWING IT UP IN AVLTREE
template<class Key, class Value>
void AVLTree<Key,Value>::rotateRight(AVLNode<Key,Value> * const oldTop)
{
    AVLNode<Key,Value> * const p = oldTop->getParent();
    AVLNode<Key,Value> * const newTop = oldTop->getLeft();
    
    oldTop->setLeft(newTop->getRight());
    
    if (oldTop->getLeft() != nullptr) {
        oldTop->getLeft()->setParent(oldTop);
    }
    
    newTop->setRight(oldTop);
    oldTop->setParent(newTop);
    
    newTop->setParent(p);
    if (p != nullptr) {
        if (p->getLeft()==oldTop) {
            p->setLeft(newTop);
        } else {
            p->setRight(newTop);
        }
    } else {
        this->root_ = newTop;
    }
}

template<class Key, class Value>
void AVLTree<Key,Value>::rotateLeft(AVLNode<Key,Value> * const oldTop)
{
    AVLNode<Key,Value> * const p = oldTop->getParent();
    AVLNode<Key,Value> * const newTop = oldTop->getRight();
    
    oldTop->setRight(newTop->getLeft());
    
    if (oldTop->getRight() != nullptr) {
        oldTop->getRight()->setParent(oldTop);
    }
    
    newTop->setLeft(oldTop);
    oldTop->setParent(newTop);
    
    newTop->setParent(p);
    if (p != nullptr) {
        if (p->getLeft()==oldTop) {
            p->setLeft(newTop);
        } else {
            p->setRight(newTop);
        }
    } else {
        this->root_ = newTop;
    }
}

template<class Key, class Value>
void AVLTree<Key,Value>::increaseRebalance(AVLNode<Key, Value>* node, bool fromLeft)
{
    if (fromLeft) {
        if (node->getLeft()->getBalance()==1) {
            innerRebalanceUtil(node, fromLeft);
        } else {
            // balance must equal -1 in this case as when you add a node there must be imbalance of one on the imbalanced side
            outerRebalanceUtil(node, fromLeft);
        }
    } else {
        if (node->getRight()->getBalance()==1) {
            outerRebalanceUtil(node, fromLeft);
        } else {
            innerRebalanceUtil(node, fromLeft);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key,Value>::decreaseRebalance(AVLNode<Key, Value>* node, bool fromLeft)
{
    AVLNode<Key, Value> * const mother = node->getParent();
    if (fromLeft) {
        switch (node->getLeft()->getBalance()) {
            case -1:
                outerRebalanceUtil(node, fromLeft);
                if (mother != nullptr) {
                    decreaseHeight(mother, onLeft(node->getParent()));
                }
                return;
            case 1:
                innerRebalanceUtil(node, fromLeft);
                if (mother != nullptr) {
                    decreaseHeight(mother, onLeft(node->getParent()));
                }
                return;
            case 0:
                bothRebalanceUtil(node, fromLeft);
                return;
        }
    } else {
        switch (node->getRight()->getBalance()) {
            case 1:
                outerRebalanceUtil(node, fromLeft);
                if (mother != nullptr) {
                    decreaseHeight(mother, onLeft(node->getParent()));
                }
                return;
            case -1:
                innerRebalanceUtil(node, fromLeft);
                if (mother != nullptr) {
                    decreaseHeight(mother, onLeft(node->getParent()));
                }
                return;
            case 0:
                bothRebalanceUtil(node, fromLeft);
                return;
        }
    }
    std::cout << "End" << std::endl;
}

template<class Key, class Value>
void AVLTree<Key,Value>::innerRebalanceUtil(AVLNode<Key,Value>* x, bool fromLeft)
{
    if (fromLeft) {
        AVLNode<Key,Value> * y = x->getLeft();
        AVLNode<Key,Value> * z = y->getRight();
        
        rotateLeft(y);
        rotateRight(x);
        
        switch (z->getBalance()) {
            case 1:
                x->setBalance(0);
                y->setBalance(-1);
                break;
            case 0:
                x->setBalance(0);
                y->setBalance(0);
                break;
            case -1:
                x->setBalance(1);
                y->setBalance(0);
                break;
        }
        z->setBalance(0);
    } else {
        AVLNode<Key,Value> * y = x->getRight();
        AVLNode<Key,Value> * z = y->getLeft();
        
        rotateRight(y);
        rotateLeft(x);
        
        switch (z->getBalance()) {
            case -1:
                x->setBalance(0);
                y->setBalance(1);
                break;
            case 0:
                x->setBalance(0);
                y->setBalance(0);
                break;
            case 1:
                x->setBalance(-1);
                y->setBalance(0);
                break;
        }
        z->setBalance(0);
    }
}

template<class Key, class Value>
void AVLTree<Key,Value>::outerRebalanceUtil(AVLNode<Key,Value>* x, bool fromLeft)
{
    if (fromLeft) {
        AVLNode<Key,Value>* const y = x->getLeft();
        rotateRight(x);
        y->setBalance(0);
    } else {
        AVLNode<Key,Value>* const y = x->getRight();
        rotateLeft(x);
        y->setBalance(0);
    }
    x->setBalance(0);
}
template<class Key, class Value>
void AVLTree<Key,Value>::bothRebalanceUtil(AVLNode<Key,Value>* x, bool fromLeft)
{
    if (fromLeft) {
        AVLNode<Key,Value>* const y = x->getLeft();
        rotateRight(x);
        x->setBalance(-1);
        y->setBalance(1);
    } else {
        AVLNode<Key,Value>* const y = x->getRight();
        rotateLeft(x);
        x->setBalance(1);
        y->setBalance(-1);
    }
}

/*
 * Recall: If key is already in the tree, you should
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &keyValuePair)
{
    if (this->root_ == nullptr) {
        this->root_ = new AVLNode<Key,Value>(keyValuePair.first, keyValuePair.second, nullptr);
        return;
    }
    
    AVLNode<Key,Value>* current = static_cast<AVLNode<Key,Value>*>(this->root_);
    
    for(;;) {
        if (keyValuePair.first == current->getKey()) {
            current->setValue(keyValuePair.second);
            return;
        }
        else if (keyValuePair.first < current->getKey()) {
            if (current->getLeft() == nullptr) {
                current->setLeft(new AVLNode<Key,Value>(keyValuePair.first,keyValuePair.second, current));
                increaseHeight(current, true);
                return;
            } else {
                current = current->getLeft();
            }
        }
        else {
            if (current->getRight() == nullptr) {
                current->setRight(new AVLNode<Key,Value>(keyValuePair.first,keyValuePair.second, current));
                increaseHeight(current, false);
                return;
            } else {
                current = current->getRight();
            }
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // do nothing if not in tree
    AVLNode<Key,Value>* removeMe = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
    if (removeMe == nullptr) {return;}
    
    if (removeMe->getLeft() != nullptr && removeMe->getRight() != nullptr) {
        
        nodeSwap(removeMe, static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::predecessor(removeMe)));
        
        AVLNode<Key,Value>* const parent = removeMe->getParent();
        bool isLeft = onLeft(removeMe);
        
        if (removeMe->getLeft() != nullptr) {
            AVLNode<Key,Value>* const promoteMe = removeMe->getLeft();
            if (isLeft) {
                parent->setLeft(promoteMe);
                promoteMe->setParent(parent);
            } else {
                parent->setRight(promoteMe);
                promoteMe->setParent(parent);
            }
        } else {
            if (isLeft) {
                parent->setLeft(nullptr);
            } else {
                parent->setRight(nullptr);
            }
        }
        decreaseHeight(parent, isLeft);
    }
    else if(removeMe->getLeft() != nullptr) {
        AVLNode<Key,Value>* const lhs = removeMe->getLeft();
        if (removeMe->getParent() == nullptr) {
            this->root_ = lhs;
            lhs->setParent(nullptr);
        } else {
            AVLNode<Key,Value>* const parent = removeMe->getParent();
            bool const left = onLeft(removeMe);
            if (left) {
                parent->setLeft(lhs);
            } else {
                parent->setRight(lhs);
            }
            lhs->setParent(parent);
            decreaseHeight(parent, left);
        }
    }
    else if(removeMe->getRight() != nullptr) {
        AVLNode<Key,Value>* const rhs = removeMe->getRight();
        if (removeMe->getParent() == nullptr) {
            this->root_ = rhs;
            rhs->setParent(nullptr);
        } else {
            AVLNode<Key,Value>* const parent = removeMe->getParent();
            bool const left = onLeft(removeMe);
            if (left) {
                parent->setLeft(rhs);
            } else {
                parent->setRight(rhs);
            }
            rhs->setParent(parent);
            decreaseHeight(parent, left);
        }
    }
    else {
        if (removeMe->getParent() == nullptr) {this->root_ = nullptr;}
        else {
            AVLNode<Key,Value>* const parent = removeMe->getParent();
            bool const left = onLeft(removeMe);
            if (left) {
                removeMe->getParent()->setLeft(nullptr);
            } else {
                removeMe->getParent()->setRight(nullptr);
            }
            decreaseHeight(parent, left);
        }
    }
    delete removeMe;
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
