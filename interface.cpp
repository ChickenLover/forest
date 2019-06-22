#include "bin_tree.h"

void print_node(BinaryTreeNode* node) {
    std::cout << "Node: key = " << node->value
              << ", left = " << (node->left ? node->left->value : -1)
              << ", right = " << (node->right ? node->right->value : -1)
              << std::endl;
}

int main() {
    BinaryTree tree{8, 12, 10, 14, 9, 11, 13, 15, 4, 2, 6, 1, 3, 5, 7};

    std::string new_line;
    std::string command;
    std::string operand;
    BinaryTreeNode* search_result = NULL;
    while(std::getline(std::cin, new_line)) {
        std::stringstream linestream(new_line);
        linestream >> command;

        if(command == "stop")
            break;

        if(command == "d_traversal") {
            std::vector<int> direct_elements = tree.direct_traversal();
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

        if(command == "print" || command == "p") {
            std::cout << tree;
            continue;
        }

        if(command == "depth" || command == "d") {
            std::cout << "Depth is: " << tree.depth() << std::endl;
            continue;
        }

        if(command == "pred") {
            if(!search_result)
                std::cout << "Make successful search operation first!" << std::endl;
            else {
                BinaryTreeNode* pred = BinaryTree::predecessor(search_result);
                if(pred)
                    print_node(pred);
                else
                    std::cout << "Not found!" << std::endl;
            }
            continue;
        }

        if(command == "succ") {
            if(!search_result)
                std::cout << "Make successful search operation first!" << std::endl;
            else {
                BinaryTreeNode* succ = BinaryTree::successor(search_result);
                if(succ)
                    print_node(succ);
                else
                    std::cout << "Not found!" << std::endl;
            }
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
            try {
                int key = std::stoi(operand);
                tree.remove(key);
            }
            catch (const std::exception& e) {
                std::cout << "Operand is not integer!" << std::endl;
            }
            continue;
        }

        if(command == "search") {
            linestream >> operand;
            try {
                int key = std::stoi(operand);
                search_result = tree.search(key);
                if(search_result)
                    print_node(search_result);
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
