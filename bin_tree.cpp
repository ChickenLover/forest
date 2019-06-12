#pragma once
#include "bin_tree.h"

void free_rec(TreeNode *node) {
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

BinaryTree::~BinaryTree() {
    free_rec(this->root);
}

void BinaryTree::insert(const int element) {
    TreeNode *node = new TreeNode({element});
    std::cout << "Inserting " << node->value << std::endl;
    if(!this->root) {
        this->root = node;
        this->t_depth = 1;
        return;
    }
    TreeNode *insert_to = this->root;
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
    this->t_depth = this->t_depth < insert_level ? insert_level : this->t_depth;
}

TreeNode* BinaryTree::search(const int key) const {
    TreeNode* node = this->root;
    while(node) {
        if(node->value == key)
            return node;
        node = key <= node->value ? node->left : node->right;
    }
    return NULL;
}

std::vector<int> BinaryTree::level_traversal() const{
    std::vector<int> elements;
    std::vector<TreeNode*> vec;
    std::vector<TreeNode*> vec2;
    vec.push_back(this->root);
    for(int level=1; level <= this->t_depth; level++){
        for(auto node: vec){
            elements.push_back(node->value);
            if(node->left)
                vec2.push_back(node->left);
            if(node->right)
                vec2.push_back(node->right);
        }
        vec = vec2;
        vec2.clear();
    }
    return elements;
}

std::vector<int> direct_traversal(const TreeNode* root) {
    std::vector<int> elements;
    if(root->left)
        elements = direct_traversal(root->left);
    elements.push_back(root->value);
    std::vector<int> right_elements;
    if(root->right)
        right_elements = direct_traversal(root->right);
    elements.reserve(elements.size() + right_elements.size());
    elements.insert(elements.end(), right_elements.begin(), right_elements.end());
    return elements;
}

int BinaryTree::depth() const {
    return this->t_depth;
}

std::vector<std::string> generate_representation(TreeNode *node, int w, char x) {
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

std::ostream &operator<< (std::ostream &os, const BinaryTree &tree) {
    /*std::vector<std::vector<int> > levels = tree.level_traversal();
    for(auto level: levels){
        for(auto value: level){
            os << value << " ";
        }
        os << std::endl;
    }*/
    char x = 2;
    int w =((1 << tree.depth()) - 1) * x;
    std::vector<std::string> lines = generate_representation(tree.root, w, x);
    for(auto line: lines)
        os << line << std::endl;
    return os;   
}