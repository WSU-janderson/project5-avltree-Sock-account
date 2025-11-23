/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <optional>
#include <ranges>
#include <vector>
using namespace std;

class AVLTree {
public:

    using KeyType = std::string;
    using ValueType = size_t;

protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;

        mutable AVLNode* left;
        mutable AVLNode* right;

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;

        size_t re_numChildren(size_t count) const;


    };

public:
   AVLTree() : root(nullptr) {

   }
    bool insert(const string& key, size_t value);

    bool remove(const string& key);

    bool contains(const string& key) const;

    bool re_contains(AVLNode *&node, string key) const;

    optional<size_t> re_get(const AVLNode*const& node, string key) const;

    size_t& re_operator_brackets(AVLNode* node,const std::string& key);

    size_t& operator[](const std::string& key);

    std::optional<size_t>get(const string& key) const;

    vector<string> re_keys() const;

    bool re_remove_keytype(AVLNode*& node, KeyType key);

    vector<string>re_findRange(AVLNode *high, AVLNode *low, vector<string> range, AVLNode * temp) const;

    vector<string>findRange(const string& lowKey, const string& highKey) const;


    vector<string> keys() const;

    size_t size() const;

    size_t getHeight() const;

    ~AVLTree();

    void re_AVLTree();
    void re_operator_equals(AVLNode * temp, const AVLNode* tree);

    friend ostream& operator<<(ostream& os, const AVLTree & avlTree);
    void re_balanceNode(AVLNode* &node);
    void operator=(const AVLTree& other);
    AVLTree(const AVLTree& other);
    private:

    AVLNode* root;
    bool re_insert(AVLNode*& node, string key,size_t value);

    bool re_remove(AVLNode*& node, string key);

    bool re_contains(AVLNode*& node, string key);
    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);
    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);

};

#endif //AVLTREE_H
