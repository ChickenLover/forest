#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <math.h>


typedef struct TreeNode {
    int value;
    TreeNode *left = NULL;
    TreeNode *right = NULL;
}TreeNode;

class BinaryTree {
    int t_depth = 0;

    public:
        TreeNode *root = NULL;
        BinaryTree() { };
        BinaryTree(std::initializer_list<int> elements);
        ~BinaryTree();
        void insert(const int element);
        TreeNode* search(const int key) const;
        void remove(const int key);
        std::vector<int> level_traversal() const;
        int depth() const;

    friend std::ostream &operator<< (std::ostream &os, const BinaryTree &tree);
};
