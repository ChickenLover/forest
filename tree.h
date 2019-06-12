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
    TreeNode *root = NULL;
    int t_depth = 0;

    public:
        BinaryTree() { };
        ~BinaryTree();
        void insert(const int element);
        bool get(const int element) const;
        void remove();
        std::vector<std::vector<int> > level_traversal() const;
        std::vector<int> direct_traversal() const;
        int depth() const;

    friend std::ostream &operator<< (std::ostream &os, const BinaryTree &tree);
};
