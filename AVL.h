//
// Created by swbro on 4/5/2023.
//

#ifndef AVL_LAB_AVL_H
#define AVL_LAB_AVL_H
#pragma once

#include "Node.h"
#include "AVLInterface.h"

class AVL : public AVLInterface {
public:
    AVL();
    ~AVL();

    Node* getRootNode() const override;

    bool insert(int data) override;

    bool remove(int data) override;

    bool contains(int data) const override;

    void clear() override;

    int size() const override;

private:
    Node* root;

    int getHeight(Node* node) const;
    int getBalance(Node* node) const;
    void updateHeight(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRightLeft(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* balance(Node* node);
    Node* insert(Node* node, int data);
    Node* findMin(Node* node) const;
    Node* remove(Node* node, int data);
    bool contains(Node* node, int data) const;
    void clear(Node* node);
    int size(Node* node) const;
    int totalSize = 0;
};

#endif