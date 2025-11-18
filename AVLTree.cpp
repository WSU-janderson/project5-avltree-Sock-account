#include "AVLTree.h"
#include <string>
#include <iostream>
using namespace std;

bool AVLTree::insert(const string& key, size_t value) {
    AVLNode* newNode = new AVLNode(key, value);
    for (int i = 0; i < value; i++) {
        if (root == nullptr) {
            root = newNode;
            return true;
        }
        if (key < root->key && root->left == nullptr) {
            root-> left = newNode;
            return true;
        }if (key < root->key && root->left != nullptr) {
            AVLNode* temp = root->left;
            while (temp !=  nullptr) {
            if (key < temp->key) {
                temp = temp->left;
            }else if (key > temp->key) {
                temp = temp->right;
            }
            }
            //Right rotation
            temp = newNode;
            if (root->left != nullptr) {
                AVLNode* tamp = root;
                AVLNode* tamp2 = root->left;
                tamp->left = nullptr;
                root = tamp2;
                root->left = tamp;
                root->right = temp;
            }
            return true;
        }
        if (key > root->key && root->right == nullptr) {
            root->right = newNode;
            return true;
        }if (key > root->key && root->right != nullptr) {
            AVLNode* temp = root->right;
            while (temp != nullptr) {
                if (key > temp->key) {
                    temp = temp->right;
                }else if (key < temp->key) {
                    temp = temp->left;
                }
            }


            //Left rotation
            temp = newNode;
            if (root->right != nullptr) {
                AVLNode* tamp = root;
                AVLNode* tamp2 = root->right;
                tamp->right = nullptr;
                root = tamp2;
                root->left = tamp;
                root->right = temp;

            }
            return true;
        }
    }
    return false;
}

bool AVLTree::remove(const string& key) {

    AVLNode* temp = root;
    if (temp->key == key) {
        root = root->right;
        root->right = nullptr;
    }
    while (temp != nullptr) {
        if (key < temp->key) {
            temp = temp->left;
            if (temp->key == key) {
                temp = nullptr;
                temp = temp->left;
            }
        }else if (key > temp->key) {
            temp = temp->right;
            if (temp->key == key) {
                temp = nullptr;
                temp = temp->left;
            }
        }

    }

    return false;
}

bool AVLTree::contains(const string& key) const {

    return false;
}

optional<size_t>AVLTree::get(const string& key) const {

    return nullopt;
}
string& AVLTree::operator[](const size_t& key) {

    return root->key;
}
vector<string> AVLTree::findRange(const string& lowKey, const string& highKey) const {

    return vector<string>();
}
vector<string> AVLTree::keys() const {

    return vector<string>();
}
AVLTree::AVLTree(const AVLTree& other) {


}
void AVLTree::operator=(const AVLTree& other) {

}
AVLTree::~AVLTree() {

}
ostream& operator<<(ostream& os, const AVLTree & avlTree) {

    return os;
}
size_t AVLTree::AVLNode::numChildren() const {

    return 0;
}

bool AVLTree::AVLNode::isLeaf() const {
    return false;
}

size_t AVLTree::AVLNode::getHeight() const {
    return 0;
}

bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}

void AVLTree::balanceNode(AVLNode *&node) {
}
