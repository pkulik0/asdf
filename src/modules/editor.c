//
// Created by pkulik0 on 01/09/2022.
//

#include "editor.h"

static editor_t editor;

#define START_COL 3
#define OPEN_FILE editor.files[editor.active_file_idx]

void editor_init() {
    editor.relative_line_num = false;

    editor.is_input_mode = false;
    editor.active_file_idx = 0;
    editor.files_size = 0;
    editor.files_capacity = 2;
    editor.files = malloc(sizeof *editor.files * editor.files_capacity);
}

void editor_destroy() {
    for(size_t i = 0; i < editor.files_size; i++) {
        file_close(&editor.files[i].file);
    }
    free(editor.files);
}

static void editor_print_file(WINDOW* w) {
    mvwprintw(w, 0, START_COL, OPEN_FILE.file.name);
    size_t offset = OPEN_FILE.line_offset;

    int y = getcury(w) + 1;
    int x = START_COL;
    int max_y = getmaxy(w)-1;

    for(size_t i = 0; i < OPEN_FILE.file.size && y < max_y; i++) {
        char current_char = OPEN_FILE.file.buffer[i];

        if(current_char == '\n') {
            if(offset <= 0) { y++; } else { offset--; }
            x = START_COL;
            continue;
        }

        if(offset != 0) continue;

        mvwprintw(w, y, x, "%c", current_char);
        x++;
    }
}

void editor_update(WINDOW* w) {
    IF_FOCUSED(box(w, 0, 0););

    if(editor.files_size > 0) {
        editor_print_file(w);
        move(OPEN_FILE.cursor.screen.y, OPEN_FILE.cursor.screen.x);
    } else {
        mvwprintw(w, 5, START_COL, "ASDF: open a file using /edit <path> or /e <path>");
    }

    static const char* const EDITOR_MODE_TABLE[] = {"VISUAL", "INPUT"};
    mvwprintw(w, getmaxy(w)-1, START_COL, EDITOR_MODE_TABLE[editor.is_input_mode]);

    wrefresh(w);
}

static void editor_open(const char* filename) {
    for(size_t i = 0; i < editor.files_size; i++) {
        if(strncmp(editor.files[i].file.name, filename, FILENAME_MAX) == 0) {
            editor.active_file_idx = i;
            return;
        }
    }

    if(editor.files_capacity <= editor.files_size) {
        editor.files_capacity *= 2;
        editor.files = realloc(editor.files, sizeof *editor.files * editor.files_capacity);
    }

    editor.active_file_idx = editor.files_size++;
    file_open(&OPEN_FILE.file, filename);
    OPEN_FILE.line_offset = 0;
    OPEN_FILE.cursor.screen = (dimensions_t){0, 0};
    OPEN_FILE.cursor.buffer = OPEN_FILE.file.buffer;
}

static void move_down() {
    if(OPEN_FILE.line_offset > 0)
        OPEN_FILE.line_offset--;
}

static void move_up() {
    OPEN_FILE.line_offset++;
}

static void switch_mode() {
    editor.is_input_mode = !editor.is_input_mode;
}

static void input_char(char c) {
    wprintw(stdscr, "%c", c);
}

static void handle_visual_mode(int key) {
    if(key == 'o' || key == KEY_DOWN) move_up();
    else if(key == 'e' || key == KEY_UP)   move_down();
}

static void handle_input_mode(int key) {
    input_char((char)key);
}

void editor_handle_key(int key) {
    if(key == KEY_HOME) {
        switch_mode();
        return;
    }

    if(editor.is_input_mode) {
        handle_input_mode(key);
    } else {
        handle_visual_mode(key);
    }
}

void editor_handle_command(const char* command) {
    if(strncmp(command, "/e", 2) == 0) {
        editor_open(&command[3]);
    }
}