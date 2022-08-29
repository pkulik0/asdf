//
// Created by pkulik0 on 29/08/2022.
//

#ifndef ASDF_TREE_H
#define ASDF_TREE_H

#include "ncurses.h"
#include "dimensions.h"

typedef struct Tree tree_t;

typedef void (*leaf_update_fn)(WINDOW*);

typedef struct Leaf {
    WINDOW* window;
    leaf_update_fn on_update;
} leaf_t;

typedef struct Branch {
    tree_t* left;
    tree_t* right;

    double split_ratio;
    bool is_horizontal;
} branch_t;

typedef enum Content {
    EMPTY,
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

tree_t* tree_create_root(dimensions_t term_size);
tree_t* tree_create_leaf(leaf_update_fn on_update);
tree_t* tree_create_branch(double split_ratio);
int tree_attach(tree_t* parent, tree_t* child);
void tree_destroy(tree_t* tree);

#endif //ASDF_TREE_H
