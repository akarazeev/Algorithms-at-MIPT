//
//  main.cpp
//  BTree
//
//  Created by Anton Karazeev on 24/05/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <vector>
#include "btree.h"

int comparator(const int& key1, const int& key2) {
    return key1 - key2;
}

int main() {

    srand((unsigned int)time(NULL));

    akarazeev::CBTree<int, int, comparator> tree(3);

    for (int i = 0; i < 20; i++)
    {
        int tmp_key = rand() % 20;
        std::cout << "> add: " << tmp_key << ' ' << tmp_key << std::endl;
        if (tree.contains(tmp_key, tmp_key)) {
            std::cout << ">> " << tmp_key << " is already there " << std::endl;
        } else {
            tree.add(tmp_key, tmp_key);
        }
    }

    puts("+___++++___+");

    tree.find(9, 9);

    for (int i = 0; i < 10; i++)
    {
        auto res = tree.find(i, i);

        if (res) {
            std::cout << "> find: " << i << ' ' << tree.get_value(i) << std::endl;
        } else {
            std::cout << "> find: " << i << ' ' << "not_found" << std::endl;
        }

        std::cout << ">> remove: " << i << ' ' << tree.remove(i, i) << std::endl;
    }

    return 0;
}
