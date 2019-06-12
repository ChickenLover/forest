#pragma once
#include "bin_tree.h"

int main() {
    BinaryTree tree{8, 12, 10, 14, 9, 11, 13, 15, 4, 2, 6, 1, 3, 5, 7};

    std::string new_line;
    std::string command;
    std::string operand;
    while(std::getline(std::cin, new_line)) {
        std::stringstream linestream(new_line);
        linestream >> command;
        if(command == "stop")
            break;
        if(command == "d_traversal") {
            std::vector<int> direct_elements = direct_traversal(tree.root);
            for(auto i: direct_elements)
                std::cout << i << " ";
            std::cout << std::endl;
            continue;
        }
        if(command == "l_traversal") {
            std::vector<int> level_elements = tree.level_traversal();
            for(auto i: level_elements)
                std::cout << i << " ";
            std::cout << std::endl;
            continue;
        }
        if(command == "print") {
            std::cout << tree;
            continue;
        }
        if(command == "insert") {
            linestream >> operand;
            try {
                int int_el = std::stoi(operand);
                tree.insert(int_el);
            }
            catch (const std::exception& e) {
                std::cout << "Operand is not integer!" << std::endl;
            }
            continue;
        }
        if(command == "remove") {
            linestream >> operand;
            continue;
        }
        if(command == "search") {
            linestream >> operand;
            try {
                int key = std::stoi(operand);
                TreeNode* node = tree.search(key);
                if(node)
                    std::cout << "Node: key = " << node->value
                              << ", left = " << (node->left ? node->left->value : -1)
                              << ", right = " << (node->right ? node->right->value : -1)
                              << std::endl;
                else
                    std::cout << "Not found!" << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << "Operand is not integer!" << std::endl;
            }
            continue;
        }
        std::cout << "No such command!" << std::endl;
    }
    return 0;
}
