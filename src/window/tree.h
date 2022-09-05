//
// Created by pkulik0 on 29/08/2022.
//

#ifndef ASDF_TREE_H
#define ASDF_TREE_H

#include "ncurses.h"
#include "dimensions.h"

typedef struct Tree tree_t;

typedef void (*leaf_update_func)(WINDOW*);
typedef void (*leaf_event_func)(const char*);
typedef void (*leaf_key_func)(int);

typedef struct Leaf {
    WINDOW* window;
    leaf_update_func on_update;
    leaf_event_func on_event;
    leaf_key_func on_key;
} leaf_t;

typedef struct Branch {
    tree_t* left;
    tree_t* right;

    double split_ratio;
    bool is_horizontal;
} branch_t;

struct Tree {
    tree_t* parent;

    dimensions_t size;
    dimensions_t position;

    enum Content {
        BRANCH,
        LEAF,
    } content;

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

tree_t* get_first_focus(tree_t* tree);
tree_t* move_focus_next(tree_t* root, tree_t* tree);
tree_t* move_focus_prev(tree_t* root, tree_t* tree);

#endif //ASDF_TREE_H
