#pragma once

#ifndef TREENODE_H
#define TREENODE_H
#endif

#include <iostream>
#include "TreeNode.h"

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, int val) {
        if (node == nullptr) return new TreeNode(val);
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else {
            node->right = insert(node->right, val);
        }
        return node;
    }

    void inorderTraversal(TreeNode* node) {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }

    TreeNode* search(TreeNode* node, int key) {
        if (node == nullptr || node->data == key) return node;
        if (key < node->data) return search(node->left, key);
        return search(node->right, key);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int val) {
        root = insert(root, val);
    }

    void inorder() {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    bool search(int key) {
        return search(root, key) != nullptr;
    }
};