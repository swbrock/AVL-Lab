#pragma once

#include "AVLInterface.h"

class AVL : public AVLInterface {
private:
    Node* root;
    int size;
    Node* insert(Node* node, int data);
    Node* remove(Node* node, int data);
    Node* findMin(Node* node);
    Node* findMax(Node* node);
    Node* findNode(Node* node, int data);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
    int getHeight(Node* node);
    void clear(Node* node);
    void print(Node* node);
public:
    AVL();
    ~AVL();
    Node* getRootNode() const;
    bool insert(int data);
    bool remove(int data);
    bool contains(int data) const;
    void clear();
    int getSize() const;
    void print();
};