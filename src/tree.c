//
// Created by pkulik0 on 29/08/2022.
//

#include "stdlib.h"
#include "tree.h"

tree_t* tree_create_window(window_t* window_ptr) {
    tree_t* tree_ptr = malloc(sizeof *tree_ptr);
    tree_ptr->content = TREE_WINDOW;

    tree_ptr->window = window_ptr;

    return tree_ptr;
}

tree_t* tree_create_branch(tree_t* left, tree_t* right) {
    tree_t* tree_ptr = malloc(sizeof *tree_ptr);
    tree_ptr->content = TREE_BRANCHES;

    tree_ptr->children.left = left;
    tree_ptr->children.right = right;

    return tree_ptr;
}

void tree_destroy(tree_t* tree_ptr) {
    if(tree_ptr->content == TREE_BRANCHES) {
        tree_destroy(tree_ptr->children.left);
        tree_destroy(tree_ptr->children.right);
    } else if (tree_ptr->content == TREE_WINDOW) {
        window_destroy(tree_ptr->window);
    }
    free(tree_ptr);
}