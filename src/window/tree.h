//
// Created by pkulik0 on 29/08/2022.
//

#ifndef ASDF_TREE_H
#define ASDF_TREE_H

#include "ncurses.h"
#include "dimensions.h"

typedef struct Tree tree_t;

typedef void (*leaf_update_func)(WINDOW*);

typedef struct Leaf {
    WINDOW* window;
    leaf_update_func on_update;
} leaf_t;

typedef struct Branch {
    tree_t* left;
    tree_t* right;

    double split_ratio;
    bool is_horizontal;
} branch_t;

typedef enum Content {
    BRANCH,
    LEAF,
} content_t;

struct Tree {
    tree_t* parent;

    dimensions_t size;
    dimensions_t position;

    content_t content;
    union {
        branch_t branch;
        leaf_t leaf;
    };
};

tree_t* tree_root(tree_t* tree);
tree_t* tree_leaf(leaf_update_func on_update);
tree_t* tree_branch(double split_ratio, bool is_horizontal, tree_t* left, tree_t* right);
void tree_destroy(tree_t* tree);

typedef void (*traverse_func)(tree_t*);

void tree_update(tree_t* tree);

leaf_t* get_first_leaf(tree_t* tree);

#endif //ASDF_TREE_H
