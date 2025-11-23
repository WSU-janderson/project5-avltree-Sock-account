#include "AVLTree.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

bool AVLTree::insert(const string& key, size_t value) {

    re_insert(root, key, value);
    //Right rotation
    AVLNode* temp = new AVLNode(key, value);

        if (root->left != nullptr) {
            AVLNode* tamp = root;
            AVLNode* tamp2 = root->left;
            tamp->left = nullptr;
            root = tamp2;
            root->left = tamp;
            root->right = temp;
            return true;
        }
        //Left rotation
        if (root->right != nullptr) {
            AVLNode* tamp = root;
            AVLNode* tamp2 = root->right;
            tamp->right = nullptr;
            root = tamp2;
            root->left = tamp;
            root->right = temp;
            return true;
        }

    return true;
}
bool AVLTree::re_insert(AVLNode*& node, string key,size_t value) {
    if (node == NULL) {
        AVLNode* newNode = new AVLNode(key, value);
        node = newNode;

        return true;
    }
    if (node->key == key) {
        return false;
    }
    if (node->key > key) {
        node->height = node->height+1;
        return re_insert(node->left, key, value);
    }if (node->key < key) {
        node->height = node->height+1;
        return re_insert(node->right, key, value);
    }

}
bool AVLTree::remove(const string& key) {


    return re_remove(root, key);

}
bool AVLTree::re_remove(AVLNode*& node, string key) {
    if (node == NULL) {
        return false;
    }
    if (node->key == key) {
        //AVLNode* temp = node->left;

        node = NULL;

        return true;
    }else if (node->key < key) {
        return re_remove(node->left, key);
    }else if (node->key > key) {
        return re_remove(node->right, key);
    }
}


bool AVLTree::contains(const string& key) const {

    AVLNode* temp = root;
    return re_contains(temp, key);

}

bool AVLTree::re_contains(AVLNode*& node, string key)const{
    if (node == NULL) {
        return false;
    }
    else if (node->key == key) {
        return true;
    }else if (node->key > key) {
        return re_contains(node->left, key);
    }else if (node->key < key) {
        return re_contains(node->right, key);
    }
return true;
}

optional<size_t>AVLTree::get(const string& key) const {



    return re_get(root,key);
}

optional<size_t> AVLTree::re_get(const AVLNode *const&node, string key) const {
        if (node == NULL) {
            return nullopt;
        }if (node->key == key) {
            return node->value;
        }if (node->key > key) {
            return re_get(node->left, key);
        }if (node->key < key) {
            return re_get(node->right, key);
        }
    return make_optional(node->value);
}

size_t& AVLTree::operator[](const std::string& key) {


    return re_operator_brackets(root, key);
}
size_t& AVLTree::re_operator_brackets( AVLNode * node,const std::string& key) {
    if (node->key == key) {
        return node->value;
    }if (node->key > key) {
        return re_operator_brackets(node->left, key);
    }if (node->key < key) {
        return re_operator_brackets(node->right, key);
    }
    return node->value;
}


//TODO:
vector<string> AVLTree::findRange(const string & lowKey, const string & highKey) const {
    AVLNode * temp = root;
    temp->key = lowKey;
    AVLNode *temp2 = root;
    temp2->key = highKey;
    vector<string> range;
    AVLNode * temp3 = root;
    return re_findRange(temp, temp2, range, temp3);

}
vector<string> AVLTree::re_findRange(AVLNode *high, AVLNode *low,vector<string> range, AVLNode * temp) const {

    if (high == NULL || low == NULL) {
        return range;
    }if (high->key == temp->key && range[0] != temp->key) {
        range.push_back(high->key);
        if (low->key == temp->key && range[0] != temp->key) {
            range.push_back(low->key);
            return re_findRange(high, low, range, temp);
        }else if (low->key > temp->key) {
            range.push_back(low->key);
            return re_findRange(high, low->right, range, temp);
        }else if (low->key < temp->key) {
            range.push_back(low->key);
            return re_findRange(high, low->left, range, temp);
        }
    }
}
vector<string> AVLTree::keys() const {
    AVLNode* temp = root;
    AVLNode* temp2 = root->right;
    int keynum = 0;
    vector<string> keys;
    while (temp->left != NULL) {
        keys[keynum] = temp->key;
        keynum++;
        if (temp->left != nullptr) {
            temp = temp->left;
        }
    }
    while (temp2->right != NULL) {
            keys[keynum] = temp2->key;
            temp2 = temp2->right;
            keynum++;
    }


    return keys;
}
AVLTree::AVLTree(const AVLTree& other) {
    AVLNode * temp = other.root;
    temp = root;
    temp->left = root->left;
    temp->right = root->right;
    temp->height = root->height;


}

void AVLTree::operator=(const AVLTree& other) {
    AVLNode * temp2 = other.root;
    AVLNode *temp = root;
    temp2 = root;
    return re_operator_equals(temp, temp2);
}
void AVLTree::re_operator_equals(AVLNode* temp,const AVLNode* other) {
    AVLNode* tamp = root;
    if (temp == NULL) {
        return;

    }if (temp->left != NULL && temp->right == NULL) {
        other->left = temp->left;
        return re_operator_equals(temp->left,other->left);
    }
    if (temp->left == NULL && temp->right != NULL) {
        other->right = temp->right;
        return re_operator_equals(temp->right,other->right);
    }
}
AVLTree::~AVLTree() {
 root= NULL;
}

ostream& operator<<(ostream& os, const AVLTree & avlTree) {

    return os;
}
size_t AVLTree::AVLNode::numChildren() const {
    size_t count = height;
    return count-1;
}


bool AVLTree::AVLNode::isLeaf() const {
    if (height > 0) {
        return true;
    }
    return false;
}

size_t AVLTree::AVLNode::getHeight() const {

    return height;
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

    return re_remove_keytype(current, key);
}
bool AVLTree::re_remove_keytype(AVLNode *&current, KeyType key) {
    if (current == NULL) {
        return false;
    }if (current->key == key) {
        current = NULL;
        return true;
    }if (current->key > key) {
        return re_remove_keytype(current->left, key);
    }if (current->key < key) {
        return re_remove_keytype(current->right, key);
    }
}
void AVLTree::balanceNode(AVLNode *&node) {
}
