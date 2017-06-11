#include <iostream>
#include "BTree.h"
#include "BTree.hpp"

int main() {
    
    BTree<int, int> my_tree(2);

//    for (int i = 0; i < 100; i++)
//    {
//        int tmp_key = rand()%100;
//        int tmp_val = rand()%100;
//        std::cout << "> add: " << tmp_key << ' ' << tmp_key << std::endl;
//        my_tree.insert(tmp_key, tmp_key);
//    }
    
    for (int i = 0; i < 10; i++)
    {
        std::cout << "> add: " << i << ' ' << i << std::endl;
        my_tree.insert(i, i);
    }
//    for (int i = 0; i < 10; i++)
//    {
//        std::cout << "> add: " << i << ' ' << i << std::endl;
//        my_tree.insert(i, i);
//    }

    for (int i = 0; i < 10; i++)
    {
        int tmp_val = my_tree.search(i);
        std::cout << "> find: " << i << ' ' << tmp_val << std::endl;
    }

    std::vector<int> to_remove = {6, 56, 89, 23, 1, 0};

    for (auto it : to_remove)
    {
        my_tree.deleteKey(it);
    }
    
    puts("> After Deleting:");
    
    for (auto it : to_remove)
    {
        int tmp_val = my_tree.search(it);
        std::cout << "> find: " << it << ' ' << tmp_val << std::endl;
    }
    
    return 0;
}
