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

#define padding(w, X, Y) wmove(w, getcury(w)+(Y), getcurx(w)+(X))

static void show_files(WINDOW* w) {
    wbkgd(w, COLOR_PAIR(2));
    mvwprintw(w, 1, 1, "FILES\n");

    padding(w, 1, 0);
    wprintw(w, "main.c\n");
    padding(w, 2, 0);
    wprintw(w, "tree.c\n");
    padding(w, 2, 0);
    wprintw(w, "tree.h\n");

    wrefresh(w);
}

static void show_editor(WINDOW* w) {
    mvwprintw(w, 1, 1, "EDITOR\n");

    padding(w, 1, 0);
    wattron(w, COLOR_PAIR(1));
    wprintw(w, "1 ");
    wattroff(w, COLOR_PAIR(1));
    wprintw(w, "def main():\n");

    int i = 2;
    padding(w, 1, 0);
    wattron(w, COLOR_PAIR(1));
    wprintw(w, "%d ", i);
    wattroff(w, COLOR_PAIR(1));
    wprintw(w, "\tprint(\"hello, world!\")\n");

    padding(w, 1, 0);
    wattron(w, COLOR_PAIR(1));
    wprintw(w, "3 ");
    wattroff(w, COLOR_PAIR(1));
    wprintw(w, "\n");

    box(w, 0, 0);
    wrefresh(w);
}

static void show_terminal(WINDOW* w) {
    wbkgd(w, COLOR_PAIR(3));
    mvwprintw(w, 1, 1, "TERMINAL\n");
    mvwprintw(w, getmaxy(w)-2, 1, "$ sudo apt-get update");

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
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

    init_color(Color(0), 50, 50, 50);
    init_color(Color(1), 80, 80, 80);
    init_pair(2, COLOR_WHITE, Color(0));
    init_pair(3, COLOR_WHITE, Color(1));

    asdf.root = tree_root(
            tree_branch(0.2, true,
                        tree_leaf(show_files),
                        tree_branch(0.75, false,
                                    tree_leaf(show_editor),
                                    tree_leaf(show_terminal)
                                    )
                        )
            );

    tree_build(asdf.root);
}

void asdf_run() {
    int keycode;
    while((keycode = getch())) {
        if(keycode == KEY_ENTER) break;
        tree_build(asdf.root);
        tree_refresh(asdf.root);
    }
}

void asdf_destroy() {
    tree_destroy(asdf.root);
    endwin();
}