#pragma once
#include "item.h"
#include <vector>

#include <iostream>
#include <string>

class BST {
public:
    BST();
    ~BST();
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void   insert(const ItemHandle& v);     // ignore duplicate (same name+cat)
    bool   contains(const ItemHandle& v) const;
    bool   erase(const ItemHandle& v);      // leaf / 1 child / 2 children
    size_t size() const { return size_; }

    void   inorder(std::vector<ItemHandle>& out) const; // ascending by operator<
    bool   isValidBST() const;                          // strict check

    void printBT()
    {
        printBT("", root_, false);
    }

private:
    struct Node {
        ItemHandle val;
        Node* left{nullptr};
        Node* right{nullptr};
        explicit Node(const ItemHandle& v) : val(v) {}
    };

    Node*  root_{nullptr};
    size_t size_{0};

    static void  clear(Node* n);
    static Node* insertNode(Node* n, const ItemHandle& v, bool& added);
    static bool  containsNode(Node* n, const ItemHandle& v);
    static bool no_children(Node* n);
    static bool one_child(Node* n);
    static bool two_children(Node* n);
    static Node* eraseRoot(Node* root, bool& erased);
    static Node* eraseNode(Node* n, const ItemHandle& v, bool& erased);
    static Node* detachMin(Node* n, Node*& minNode);
    static void  inorderWalk(Node* n, std::vector<ItemHandle>& out);
    static bool  isValid(Node* n, const ItemHandle* lo, const ItemHandle* hi);

    void printBT(std::string prefix, const Node* node, bool isLeft)
    {
        if( node != nullptr )
        {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──" );

            // print the value of the node
            std::cout << node->val << std::endl;

            // enter the next tree level - left and right branch
            printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
            printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
        }
    }
};
