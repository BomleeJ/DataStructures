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
    
    if (n == nullptr) { 
        added = true;
        return new Node(v);
    }

    
    
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
    if (contains(v)) { return; }
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
BST::Node* BST::detachMin(Node* RSTRoot, Node*& minNode) {
/*minnode is replacement! we simply need to addign minNode and delete its current presence*/
if (RSTRoot->left == nullptr)
{
    minNode = RSTRoot;
    return RSTRoot->right; /*new RST Root Technically will be nullptr if childless*/
}

RSTRoot->left = detachMin(RSTRoot->left, minNode);
return RSTRoot;
}


bool BST::no_children(Node* n) { return (n->right == nullptr && n->left == nullptr); }
bool BST::one_child(Node* n) { return !(no_children(n) || two_children(n)); }
bool BST::two_children(Node* n) { return (n->right != nullptr && n->left != nullptr); }

// Helper to eraseRoot returns new Root
BST::Node* BST::eraseRoot(Node* root, bool& erased)
{  
    erased = true;
    if (no_children(root))
    {
        delete root;
        return nullptr; // Will be returned to root_ in call stack 
    }
    else if (one_child(root))
    {
        Node* child = (root->left == nullptr) ? root->right : root->left;
        delete root;
        return child;
    }
    else
    {
        Node* RSTRoot = root->right;
        Node* Successor = nullptr;
        RSTRoot = detachMin(RSTRoot, Successor); 
        Successor->right = RSTRoot;
        Successor->left = root->left;
        delete root;
        return Successor;
    }
    
}

// TODO: Implement erase (leaf / one child / two children via successor)
BST::Node* BST::eraseNode(Node* n, const ItemHandle& v, bool& erased) {
    if (n == nullptr) { return n; }

    if (n->val == v)
    {
        return eraseRoot(n, erased);
    }

    if (n->val < v)
    {
        n->right = eraseNode(n->right, v, erased);
        return n;
    }
    else
    {
        n->left = eraseNode(n->left, v, erased);
        return n;
    }
    
}

bool BST::erase(const ItemHandle& v) {
    bool erased = false;
    root_ = eraseNode(root_, v, erased);
    if (erased) --size_;
    return erased;
}
