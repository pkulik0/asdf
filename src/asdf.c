//
// Created by pkulik0 on 29/08/2022.
//

#include "ncurses.h"
#include "asdf.h"

#include "modules/editor.h"

static void show_files(WINDOW* w) {
    wbkgd(w, COLOR_PAIR(2));
    mvwprintw(w, 1, 1, "FILES\n");

    IF_FOCUSED(
            mvwprintw(w, 3, 1, "SELECTED\n");
            box(w, 0, 0);
            )

    wrefresh(w);
}

static void show_terminal(WINDOW* w) {
    wbkgd(w, COLOR_PAIR(3));
    mvwprintw(w, 1, 1, "TERMINAL\n");

    IF_FOCUSED(
            mvwprintw(w, 3, 1, "SELECTED\n");
            box(w, 0, 0);
    )

    wrefresh(w);
}

static void ncurses_init() {
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
}

void asdf_init() {
    editor_init();
    editor_handle_command("/e asdf.c");

    ncurses_init();

    asdf.root = tree_root(tree_branch(0.15, true,
                        tree_leaf(show_files),
                        tree_branch(0.80, false,
                                    tree_leaf(editor_update),
                                    tree_leaf(show_terminal))));
}

void asdf_run() {
    tree_update(asdf.root);
    asdf.focused = get_next_focus(asdf.root);
    asdf.size = (dimensions_t){getmaxx(stdscr), getmaxy(stdscr)};

    int key;
    while((key = getch())) {
        if(key == '\t') {
            asdf.focused = get_next_focus(asdf.focused);
        } else {
            editor_handle_key(key);
        }
        tree_update(asdf.root);
    }
}

void asdf_destroy() {
    tree_destroy(asdf.root);
    editor_destroy();
    endwin();
}