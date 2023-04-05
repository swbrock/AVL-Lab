//
// Created by swbro on 4/5/2023.
//
#include "node.h"
#include "AVL.h"
#include "AVLInterface.h"

AVL::~AVL() {
    clear();
}

Node *AVL::getRootNode() const {
    return root;
}

bool AVL::insert(int data) {
    if (root == nullptr) {
        root = new Node(data);
        totalSize++;
        return true;
    }
    Node *current = root;
    while (current != nullptr) {
        if (data < current->data) {
            if (current->left == nullptr) {
                current->left = new Node(data);
                totalSize++;
                return true;
            }
            current = current->left;
        } else if (data > current->data) {
            if (current->right == nullptr) {
                current->right = new Node(data);
                totalSize++;
                return true;
            }
            current = current->right;
        } else {
            return false;
        }
    }
    return false;
}

bool AVL::remove(int data) {
    if (root == nullptr) {
        return false;
    }
    Node *current = root;
    Node *parent = nullptr;
    while (current != nullptr) {
        if (data < current->data) {
            parent = current;
            current = current->left;
        } else if (data > current->data) {
            parent = current;
            current = current->right;
        } else {
            if (current->left == nullptr && current->right == nullptr) {
                if (parent == nullptr) {
                    root = nullptr;
                } else if (parent->left == current) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
                delete current;
                totalSize--;
                return true;
            } else if (current->left == nullptr) {
                if (parent == nullptr) {
                    root = current->right;
                } else if (parent->left == current) {
                    parent->left = current->right;
                } else {
                    parent->right = current->right;
                }
                delete current;
                totalSize--;
                return true;
            } else if (current->right == nullptr) {
                if (parent == nullptr) {
                    root = current->left;
                } else if (parent->left == current) {
                    parent->left = current->left;
                } else {
                    parent->right = current->left;
                }
                delete current;
                totalSize--;
                return true;
            } else {
                Node *successor = current->right;
                Node *successorParent = current;
                while (successor->left != nullptr) {
                    successorParent = successor;
                    successor = successor->left;
                }
                current->data = successor->data;
                if (successorParent->left == successor) {
                    successorParent->left = successor->right;
                } else {
                    successorParent->right = successor->right;
                }
                delete successor;
                totalSize--;
                return true;
            }
        }
    }
    return false;
}

bool AVL::contains(int data) const {
    Node *current = root;
    while (current != nullptr) {
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            return true;
        }
    }
    return false;
}

void AVL::clear() {
    while (root != nullptr) {
        remove(root->data);
    }
}

int AVL::size() const {
    return totalSize;
}