//
// Created by pkulik0 on 29/08/2022.
//

#include "stdlib.h"
#include "tree.h"

tree_t* tree_root(tree_t* tree) {
    tree->parent = NULL;
    tree->position = (dimensions_t){0, 0};
    return tree;
}

tree_t* tree_leaf(leaf_update_func on_update) {
    tree_t* tree = malloc(sizeof *tree);
    tree->content = LEAF;

    tree->leaf.window = NULL;
    tree->leaf.on_update = on_update;

    return tree;
}

tree_t* tree_branch(double split_ratio, bool is_horizontal, tree_t* left, tree_t* right) {
    tree_t* tree = malloc(sizeof *tree);
    tree->content = BRANCH;

    tree->branch.split_ratio = split_ratio;
    tree->branch.is_horizontal = is_horizontal;

    left->parent = tree;
    right->parent = tree;

    tree->branch.left = left;
    tree->branch.right = right;

    return tree;
}

void tree_traverse(tree_t* tree, traverse_func do_work) {
    do_work(tree);
    if(tree->content == BRANCH) {
        tree_traverse(tree->branch.left, do_work);
        tree_traverse(tree->branch.right, do_work);
    }
}

static void __tree_build(tree_t* tree) {
    if(tree->content == LEAF) {
        tree->leaf.window = newwin(tree->size.y, tree->size.x, tree->position.y, tree->position.x);
        return;
    }

    branch_t* branch = &tree->branch;

    dimensions_t* size = &tree->size;
    dimensions_t* pos = &tree->position;
    dimensions_t scaled = (dimensions_t){size->x*branch->split_ratio, size->y*branch->split_ratio};

    tree_t* left = branch->left;
    tree_t* right = branch->right;

    // Move scaled size down the tree
    left->position = *pos;
    if(branch->is_horizontal) {
        left->size = (dimensions_t){scaled.x, size->y};
        right->size = (dimensions_t){size->x - scaled.x, size->y};
        right->position = (dimensions_t){pos->x + scaled.x, pos->y};
    } else {
        left->size = (dimensions_t){size->x, scaled.y};
        right->size = (dimensions_t){size->x, size->y - scaled.y};
        right->position = (dimensions_t) {pos->x, pos->y + scaled.y};
    }
}

void tree_build(tree_t* tree) {
    if(!tree->parent)
        tree->size = (dimensions_t){getmaxx(stdscr), getmaxy(stdscr)};

    tree_traverse(tree, __tree_build);
}

static void __tree_refresh(tree_t* tree) {
    if(tree->content != LEAF) return;
    tree->leaf.on_update(tree->leaf.window);
}

void tree_refresh(tree_t* tree) {
    tree_traverse(tree, __tree_refresh);
}


void tree_destroy(tree_t* tree) {
    if(tree->content == BRANCH) {
        tree_destroy(tree->branch.left);
        tree_destroy(tree->branch.right);
    } else if (tree->content == LEAF) {
        delwin(tree->leaf.window);
    }
    free(tree);
}