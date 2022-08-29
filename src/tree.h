//
// Created by pkulik0 on 29/08/2022.
//

#ifndef ASDF_TREE_H
#define ASDF_TREE_H

#include "ncurses.h"
#include "dimensions.h"

typedef struct Tree tree_t;

typedef struct Branches {
    tree_t * left;
    tree_t * right;
    double split_ratio;
    bool is_horizontal;
} branches_t;

typedef enum Content {
    TREE_BRANCHES, TREE_WINDOW
} content_t;

struct Tree {
    dimensions_t size;
    dimensions_t position;

    union {
        branches_t children;
        WINDOW* window;
    };
    content_t content;
};

tree_t* tree_create_root(dimensions_t term_size);
tree_t* tree_create_leaf();
tree_t* tree_create_branch(double split_ratio);
int tree_attach(tree_t* parent, tree_t* child);
void tree_destroy(tree_t* tree);

#endif //ASDF_TREE_H
