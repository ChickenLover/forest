#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <math.h>


typedef struct BinaryTreeNode {
    int value;
    BinaryTreeNode *left = NULL;
    BinaryTreeNode *right = NULL;
}BinaryTreeNode;


class BinaryTree {
    int t_depth = -1;
    BinaryTreeNode *root = NULL;

    public:
        BinaryTree() { };
        BinaryTree(std::initializer_list<int> elements);
        BinaryTree(BinaryTreeNode *root);
        ~BinaryTree();
        void insert(const int element);
        BinaryTreeNode* search(const int key) const;
        void remove(const int key);
        std::vector<int> level_traversal() const;
        std::vector<int> direct_traversal() const;
        int depth();
        static void free_rec(BinaryTreeNode *node);
        static std::vector<int> _direct_traversal(const BinaryTreeNode* node);
        static int _depth(const BinaryTreeNode* node);
        static BinaryTreeNode* successor(BinaryTreeNode *node);
        static BinaryTreeNode* predecessor(BinaryTreeNode *node);
        static std::vector<std::string> generate_representation(BinaryTreeNode *node, int w, char x);

    friend std::ostream &operator<< (std::ostream &os, BinaryTree &tree);
};
