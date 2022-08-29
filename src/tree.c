//
// Created by pkulik0 on 29/08/2022.
//

#include "stdlib.h"
#include "tree.h"

tree_t* tree_create_root(dimensions_t term_size) {
    tree_t* tree = tree_create_branch(1.0);
    tree->position = (dimensions_t){0, 0};
    tree->size = term_size;
    return tree;
}

tree_t* tree_create_leaf() {
    tree_t* tree = malloc(sizeof *tree);
    tree->content = TREE_WINDOW;
    tree->window = NULL;

    return tree;
}

tree_t* tree_create_branch(double split_ratio) {
    tree_t* tree = malloc(sizeof *tree);
    tree->content = TREE_BRANCHES;

    tree->children.split_ratio = split_ratio;
    tree->children.is_horizontal = true;
    tree->children.left = NULL;
    tree->children.right = NULL;

    return tree;
}

void tree_destroy(tree_t* tree) {
    if(tree->content == TREE_BRANCHES) {
        tree_destroy(tree->children.left);
        tree_destroy(tree->children.right);
    } else if (tree->content == TREE_WINDOW) {
        delwin(tree->window);
    }
    free(tree);
}

int tree_attach(tree_t* parent, tree_t* child) {
    if(parent->content != TREE_BRANCHES) return -1;
    if(parent->children.split_ratio == 1.0 && parent->children.left) return -2;

    branches_t* b = &parent->children;
    dimensions_t scaled = dimensions_scale(parent->size, b->split_ratio);

    if(!b->left) {
        if(b->is_horizontal) {
            child->size = (dimensions_t){scaled.x, parent->size.y};
        } else {
            child->size = (dimensions_t){parent->size.x, scaled.y};
        }
        child->position = parent->position;
        parent->children.left = child;
    } else if(!b->right) {
        if(b->is_horizontal) {
            child->size = (dimensions_t){parent->size.x - scaled.x, parent->size.y};
            child->position = (dimensions_t){parent->position.x + scaled.x, parent->position.y};
        } else {
            child->size = (dimensions_t){parent->size.x, parent->size.y - scaled.y};
            child->position = (dimensions_t) {parent->position.x, parent->position.y + scaled.y};
        }
        parent->children.right = child;
    } else {
        return -3;
    }

    if(child->content == TREE_WINDOW) {
        child->window = newwin(child->size.y, child->size.x, child->position.y, child->position.x);
        box(child->window, 0, 0);
        wprintw(child->window, "hello");
        wrefresh(child->window);
    }

    return 0;
}