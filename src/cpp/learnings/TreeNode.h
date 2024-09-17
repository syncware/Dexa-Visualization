#pragma once

#ifndef TREENODE_H
#define TREENODE_H
#endif

#include <iostream>

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr; 
    }
};