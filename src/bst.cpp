#include "bst.h"

BST::BST() = default;
BST::~BST() { clear(root_); }

void BST::clear(Node* n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// TODO: Implement insert (ignore duplicate)
BST::Node* BST::insertNode(Node* n, const ItemHandle& v, bool& added) {
    if (n == nullptr) { return new Node(v); }
    Node* curr = n;
    Node* prev = nullptr;
    added = false;
    while(curr != nullptr)
    {
        prev = curr;
        if(curr->val < v)
        {
            curr = curr->right;
        }
        else if (v < curr->val)
        {
            curr = curr->left;
        }
        else
        {
            return n;
        }
    }

    added = true;

    if (prev->val < v)
    {
        prev->right = new Node(v);
    }
    else
    {
        prev->left = new Node(v);
    }
    
    
    
    return n; // STUB
}

void BST::insert(const ItemHandle& v) {
    bool added = false;
    root_ = insertNode(root_, v, added);
    if (added) ++size_;
}

// TODO: Implement contains
bool BST::containsNode(Node* n, const ItemHandle& v) {
    if (n == nullptr) { return false; }

    if (n->val == v) { return true; }

    if (n->val < v)
        return containsNode(n->right, v);
    else
        return containsNode(n->left, v);    

}
bool BST::contains(const ItemHandle& v) const { return containsNode(root_, v); }

// TODO: Implement inorder traversal
void BST::inorderWalk(Node* n, std::vector<ItemHandle>& out) {
    if (n == nullptr) { return; }
    inorderWalk(n->left, out);
    out.push_back(n->val);
    inorderWalk(n->right, out);

}
void BST::inorder(std::vector<ItemHandle>& out) const { out.clear(); inorderWalk(root_, out); }

// TODO: Implement validity check (strict BST)
bool BST::isValid(Node* n, const ItemHandle* lo, const ItemHandle* hi) {

    if (n == nullptr) { return true; }

    bool curr_valid = (lo == nullptr || *lo < n->val) && (hi == nullptr || n->val < *hi);

    if (!curr_valid) { return false; }

    /* For LST hi is n->val*/ /* for RST lo is n->val*/
    bool l_valid = isValid(n->left, lo, &n->val);
    bool r_valid = isValid(n->right, &n->val, hi);

    return l_valid && r_valid; // STUB (kept true so tests progress past basic check)
}
bool BST::isValidBST() const { return isValid(root_, nullptr, nullptr); }

// Helper for two-child delete (successor)
BST::Node* BST::detachMin(Node* n, Node*& minNode) {
    while (n->left->left != nullptr)
    {
        n = n->left;
    }
    minNode = n->left;
    n->left = nullptr;
    return n;
}

// TODO: Implement erase (leaf / one child / two children via successor)
BST::Node* BST::eraseNode(Node* n, const ItemHandle& v, bool& erased) {
    erased = false;
    Node* curr = n;
    Node* prev = nullptr;
    while(curr)
    {
        
        if (curr->val < v)
        {
            curr = curr->left;
        }
        else if (v < curr->val)
        {
            curr = curr->right;
        }
        else
        {
            break;
        }
        prev = curr;
    }

    if (curr == nullptr) { return n; }

    bool no_children = (prev->right == nullptr && prev->left == nullptr);
    bool two_children = (prev->right != nullptr && prev->left != nullptr);
    bool one_child = !(no_children || two_children);

    if(no_children)
    {
        if (prev->left->val == v)
        {
            prev->left = nullptr;
        }
        else
        {
            prev->right = nullptr;
        }
    }
    else if (one_child)
    {
        Node* child = (curr->left == nullptr) ? curr->right : curr->left;
        if (prev->left->val == v)
        {
            prev->left = child;
        }
        else
        {
            prev->right = child;
        }
    }
    else
    {
        Node* minNode = nullptr;
        detachMin(curr->right, minNode);
        if (prev->left->val == v)
        {
            prev->left = minNode;
        }
        else
        {
            prev->right = minNode;
        }

    }
    return n; // STUB
}

bool BST::erase(const ItemHandle& v) {
    bool erased = false;
    root_ = eraseNode(root_, v, erased);
    if (erased) --size_;
    return erased;
}
