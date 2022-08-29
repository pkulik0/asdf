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
    t2->children.is_horizontal = false;

    tree_attach(t1, tree_create_leaf());
    tree_attach(t1, t2);

    tree_attach(t2, tree_create_leaf());
    tree_attach(t2, tree_create_leaf());





}

void asdf_run() {
    getch();
}

void asdf_destroy() {
    endwin();
}