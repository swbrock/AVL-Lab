#include "AVL.h"
using namespace std;

AVL::AVL() {
    root = NULL;
    size = 0;
}

AVL::~AVL() {
    clear();
}

Node* AVL::getRootNode() const {
    return root;
}

bool AVL::insert(int data) {
    root = insert(root, data);
    return true;
}

Node* AVL::insert(Node* node, int data) {
    if (node == NULL) {
        node = new Node(data);
        size++;
    }
    else if (data < node->data) {
        node->left = insert(node->left, data);
        if (getHeight(node->left) - getHeight(node->right) == 2) {
            if (data < node->left->data) {
                node = rotateLeft(node);
            }
            else {
                node = rotateLeftRight(node);
            }
        }
    }
    else if (data > node->data) {
        node->right = insert(node->right, data);
        if (getHeight(node->right) - getHeight(node->left) == 2) {
            if (data > node->right->data) {
                node = rotateRight(node);
            }
            else {
                node = rotateRightLeft(node);
            }
        }
    }
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    return node;
}

bool AVL::remove(int data) {
    root = remove(root, data);
    return true;
}

Node* AVL::remove(Node* node, int data) {
    if (node == NULL) {
        return node;
    }
    else if (data < node->data) {
        node->left = remove(node->left, data);
        if (getHeight(node->right) - getHeight(node->left) == 2) {
            if (getHeight(node->right->left) > getHeight(node->right->right)) {
                node = rotateRightLeft(node);
            }
            else {
                node = rotateRight(node);
            }
        }
    }
    else if (data > node->data) {
        node->right = remove(node->right, data);
        if (getHeight(node->left) - getHeight(node->right) == 2) {
            if (getHeight(node->left->right) > getHeight(node->left->left)) {
                node = rotateLeftRight(node);
            }
            else {
                node = rotateLeft(node);
            }
        }
    }
    else {
        if (node->left == NULL && node->right == NULL) {
            delete node;
            node = NULL;
            size--;
        }
        else if (node->left == NULL) {
            Node* temp = node;
            node = node->right;
            delete temp;
            size--;
        }
        else if (node->right == NULL) {
            Node* temp = node;
            node = node->left;
            delete temp;
            size--;
        }
        else {
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
    }
    if (node != NULL) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }
    return node;
}

bool AVL::contains(int data) const {
    return findNode(root, data) != NULL;
}

Node* AVL::findMin(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    else if (node->left == NULL) {
        return node;
    }
    else {
        return findMin(node->left);
    }
}

Node* AVL::findMax(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    else if (node->right == NULL) {
        return node;
    }
    else {
        return findMax(node->right);
    }
}

Node* AVL::findNode(Node* node, int data) {
    if (node == NULL) {
        return NULL;
    }
    else if (data < node->data) {
        return findNode(node->left, data);
    }
    else if (data > node->data) {
        return findNode(node->right, data);
    }
    else {
        return node;
    }
}

Node* AVL::rotateLeft(Node* node) {
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    temp->height = max(getHeight(temp->left), node->height) + 1;
    return temp;
}

Node* AVL::rotateRight(Node* node) {
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    temp->height = max(getHeight(temp->right), node->height) + 1;
    return temp;
}

Node* AVL::rotateLeftRight(Node* node) {
    node->left = rotateRight(node->left);
    return rotateLeft(node);
}

Node* AVL::rotateRightLeft(Node* node) {
    node->right = rotateLeft(node->right);
    return rotateRight(node);
}

int AVL::getHeight(Node* node) {
    if (node == NULL) {
        return -1;
    }
    else {
        return node->height;
    }
}

void AVL::clear() {
    clear(root);
    root = NULL;
    size = 0;
}

void AVL::clear(Node* node) {
    if (node != NULL) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

int AVL::getSize() const {
    return size;
}

bool AVL::isEmpty() const {
    return size == 0;
}

void AVL::printTree() const {
    printTree(root);
}

void AVL::printTree(Node* node) const {
    if (node != NULL) {
        printTree(node->left);
        cout << node->data << " ";
        printTree(node->right);
    }
}
