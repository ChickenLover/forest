#include "bin_tree.h"


void BinaryTree::free_rec(BinaryTreeNode *node) {
    if(node) {
        free_rec(node->left);
        free_rec(node->right);
        delete node;
    }
}

BinaryTree::BinaryTree(std::initializer_list<int> elements) {
    for(int element: elements)
        this->insert(element);
}

BinaryTree::BinaryTree(BinaryTreeNode *root) {
    this->root = root;
    this->depth(); // Recalculate height
}

BinaryTree::~BinaryTree() {
    free_rec(this->root);
}

void BinaryTree::insert(const int element) {
    BinaryTreeNode *node = new BinaryTreeNode({element});
    std::cout << "Inserting " << node->value << std::endl;
    if(!this->root) {
        this->root = node;
        this->t_depth = 1;
        return;
    }
    BinaryTreeNode *insert_to = this->root;
    int insert_level = 2;
    for(; true; insert_level++) {
        if(element > insert_to->value){
            if(!insert_to->right) {
                insert_to->right = node;
                break;
            }
            insert_to = insert_to->right;
        }
        else {
            if(!insert_to->left) {
                insert_to->left = node;
                break;
            }
            insert_to = insert_to->left;
        }
    }
    this->t_depth = std::max(this->depth(), insert_level);
}

BinaryTreeNode* BinaryTree::search(const int key) const {
    BinaryTreeNode* node = this->root;
    while(node) {
        if(node->value == key)
            return node;
        node = key <= node->value ? node->left : node->right;
    }
    return NULL;
}

void BinaryTree::remove(const int key) {
    if(!this->root)
        return;

    // Find node and his parent =================
    BinaryTreeNode* parent = NULL;
    BinaryTreeNode* node = this->root;
    bool child_left = false;
    do {
        if(node->value == key)
            break;
        parent = node;
        if(key <= node->value) {
            node = node->left;
            child_left = true;
        }
        else {
            node = node->right;
            child_left = false;
        }
    } while(node);
    if(!node)
        return;
    // ========================================

    // Find replacement and replace
    BinaryTreeNode* replacement = NULL;
    if(node->left && node->right) {
        replacement = node->right;
        if(replacement->left) {
            BinaryTreeNode* replace_parent = node;
            while(replacement->left) {
                replace_parent = replacement;
                replacement = replacement->left;
            }
            replace_parent->left = NULL;
            replacement->right = node->right;
        }
        replacement->left = node->left;
    }
    else {
        replacement = node->left ? node->left : node->right;
    }
    if(parent) {
        if(child_left)
            parent->left = replacement;
        else
            parent->right = replacement;
    }
    else
        this->root = replacement;
    delete node;
    this->t_depth = -1; // As we don't know if depth had decreemented, set depth to unknown
}

BinaryTreeNode* BinaryTree::successor(BinaryTreeNode* node) {
    if(!node || !node->right)
        return NULL;
    BinaryTreeNode* s_node = node->right;
    while(s_node->left)
        s_node = s_node->left;
    return s_node;
}

BinaryTreeNode* BinaryTree::predecessor(BinaryTreeNode* node) {
    if(!node || !node->left)
        return NULL;
    BinaryTreeNode* p_node = node->left;
    while(p_node->right)
        p_node = p_node->right;
    return p_node;
}

std::vector<int> BinaryTree::level_traversal() const{
    std::vector<int> elements;
    std::vector<BinaryTreeNode*> vec;
    std::vector<BinaryTreeNode*> vec2;
    vec.push_back(this->root);
    while(vec2.size()){
        for(auto node: vec){
            elements.push_back(node->value);
            if(node->left)
                vec2.push_back(node->left);
            if(node->right)
                vec2.push_back(node->right);
        }
        vec = vec2; // Swap
        vec2.clear();
    }
    return elements;
}


std::vector<int> BinaryTree::direct_traversal() const{
    return _direct_traversal(this->root);
}


std::vector<int> BinaryTree::_direct_traversal(const BinaryTreeNode* node) {
    std::vector<int> elements;
    if(node->left)
        elements = _direct_traversal(node->left);
    elements.push_back(node->value);
    std::vector<int> right_elements;
    if(node->right)
        right_elements = _direct_traversal(node->right);
    elements.reserve(elements.size() + right_elements.size());
    elements.insert(elements.end(), right_elements.begin(), right_elements.end());
    return elements;
}

int BinaryTree::_depth(const BinaryTreeNode *node) {
    if(!node)
        return 0;
    return std::max(_depth(node->left),  _depth(node->right)) + 1;
}

int BinaryTree::depth() {
    if(this->t_depth == -1) {
        this->t_depth = _depth(this->root);
    }
    return this->t_depth;
}

std::vector<std::string> BinaryTree::generate_representation(BinaryTreeNode *node, int w, char x) {
    std::vector<std::string> lines;
    std::ostringstream ss;
    // ss << std::setfill('0');
    ss << std::setw(x) << std::to_string(node->value);
    std::string str_value = ss.str();
    ss.str(std::string());
    if(w <= x){
        lines.push_back(str_value);
        return lines;
    }
    int half = (w - x) / 2;
    int next_half = (half - x) / 2;
    std::vector<std::string> left_lines;
    std::vector<std::string> right_lines;
    if(node->left)
        left_lines = generate_representation(node->left, half, x);
    if(node->right)
        right_lines = generate_representation(node->right, half, x);
    ss << std::setfill(' ');
    ss << std::setw(half) << " " << str_value << std::setw(half) << " ";
    lines.push_back(ss.str());
    ss.str(std::string());
    int skip = int(sqrt((half - next_half) / x));
    for(int i=half-1; i>=next_half; i-= skip) {
        if(i)
            ss << std::setw(i) << " ";
        ss << (node->left ? "/" : " ");
        if(half - i)
            ss << std::setw(2 * (half - i) - 1) << " ";
        ss << (node->right ? "\\" : " ") << std::setw(i + x - 1) << " ";
        lines.push_back(ss.str());
        ss.str(std::string());
    }
    for(int i=0; i<std::max(left_lines.size(), right_lines.size()); i++) {
        if(i < left_lines.size())
            ss << left_lines[i];
        else
            ss << std::setw(half) << " ";
        ss << std::setw(x) << " ";
        if(i < right_lines.size())
            ss << right_lines[i];
        else
            ss << std::setw(half) << " ";
        lines.push_back(ss.str());
        ss.str(std::string());
    }
    return lines;
}

std::ostream &operator<< (std::ostream &os, BinaryTree &tree) {
    if(!tree.root)
        return os;
    char x = 2;
    int w =((1 << tree.depth()) - 1) * x;
    std::vector<std::string> lines = BinaryTree::generate_representation(tree.root, w, x);
    for(auto line: lines)
        os << line << std::endl;
    return os;   
}
