//
// Created by pkulik0 on 29/08/2022.
//

#include "stdlib.h"
#include "tree.h"

tree_t* tree_create_root(dimensions_t term_size) {
    tree_t* tree = tree_create_branch(1.0);
    tree->parent = NULL;
    tree->position = (dimensions_t){0, 0};
    tree->size = term_size;
    return tree;
}

tree_t* tree_create_leaf(leaf_update_fn on_update) {
    tree_t* tree = malloc(sizeof *tree);
    tree->content = LEAF;
    tree->leaf.window = NULL;
    tree->leaf.on_update = on_update;

    return tree;
}

tree_t* tree_create_branch(double split_ratio) {
    tree_t* tree = malloc(sizeof *tree);
    tree->content = BRANCH;

    tree->branch.split_ratio = split_ratio;
    tree->branch.is_horizontal = true;
    tree->branch.left = NULL;
    tree->branch.right = NULL;

    return tree;
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

int tree_attach(tree_t* parent, tree_t* child) {
    if(parent->content != BRANCH) return -1;
    if(parent->branch.split_ratio == 1.0 && parent->branch.left) return -2;

    child->parent = parent;

    branch_t* branch = &parent->branch;
    dimensions_t scaled = dimensions_scale(parent->size, branch->split_ratio);

    if(!branch->left) {
        if(branch->is_horizontal) {
            child->size = (dimensions_t){scaled.x, parent->size.y};
        } else {
            child->size = (dimensions_t){parent->size.x, scaled.y};
        }
        child->position = parent->position;
        branch->left = child;
    } else if(!branch->right) {
        if(branch->is_horizontal) {
            child->size = (dimensions_t){parent->size.x - scaled.x, parent->size.y};
            child->position = (dimensions_t){parent->position.x + scaled.x, parent->position.y};
        } else {
            child->size = (dimensions_t){parent->size.x, parent->size.y - scaled.y};
            child->position = (dimensions_t) {parent->position.x, parent->position.y + scaled.y};
        }
        branch->right = child;
    } else {
        return -3;
    }

    if(child->content == LEAF) {
        child->leaf.window = newwin(child->size.y, child->size.x, child->position.y, child->position.x);
    }

    return 0;
}