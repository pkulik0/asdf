//
// Created by pkulik0 on 29/08/2022.
//

#include "ncurses.h"
#include "asdf.h"
#include "tree.h"

typedef struct Asdf {
    tree_t* root;
} asdf_t;

asdf_t asdf;

static void print_sth(WINDOW* w) {
    static int count = 0;
    box(w, 0, 0);
    mvwprintw(w, 1, 1, "Window %d", count++);
    wrefresh(w);
}

void asdf_init() {
    // Initialize ncurses
    initscr();
    raw();
    noecho();
    nonl();
    intrflush(stdscr, false);
    keypad(stdscr, true);
    start_color();

    asdf.root = tree_create_root((dimensions_t){getmaxx(stdscr), getmaxy(stdscr)});

    tree_t* t1 = tree_create_branch(0.2);
    tree_attach(asdf.root, t1);

    tree_t* t2 = tree_create_branch(0.8);
    t2->branch.is_horizontal = false;

    tree_attach(t1, tree_create_leaf(print_sth));
    tree_attach(t1, t2);

    tree_attach(t2, tree_create_leaf(print_sth));
    tree_attach(t2, tree_create_leaf(print_sth));
}

void update_tree(tree_t* tree) {
    if(!tree) return;

    if(tree->content == LEAF) {
        tree->leaf.on_update(tree->leaf.window);
    } else if (tree->content == BRANCH) {
        update_tree(tree->branch.left);
        update_tree(tree->branch.right);
    }
}

void asdf_run() {
    getch();
    update_tree(asdf.root);
    getch();
    update_tree(asdf.root);
    getch();
}

void asdf_destroy() {
    endwin();
}