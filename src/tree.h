//
// Created by pkulik0 on 29/08/2022.
//

#ifndef ASDF_TREE_H
#define ASDF_TREE_H

#include "window.h"

typedef struct Tree tree_t;

typedef struct Branches {
    tree_t * left;
    tree_t * right;
} branches_t;

typedef enum Content {
    TREE_EMPTY, TREE_BRANCHES, TREE_WINDOW
} content_t;

struct Tree {
    union {
        branches_t children;
        window_t* window;
    };
    content_t content;
};

tree_t* tree_create_window(window_t* window_ptr);
tree_t* tree_create_branch(tree_t* left_ptr, tree_t* right_ptr);
void attach_to_tree(tree_t* tree_ptr, tree_t* tree_child_ptr);
void tree_destroy(tree_t* tree_ptr);

#endif //ASDF_TREE_H
