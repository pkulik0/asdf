//
// Created by pkulik0 on 01/09/2022.
//

#include "editor.h"

static editor_t editor;

void editor_init() {
    editor.active_file_idx = 0;
    editor.files_size = 0;
    editor.files_capacity = 2;
    editor.files = malloc(sizeof *editor.files * editor.files_capacity);
}

void editor_destroy() {
    for(size_t i = 0; i < editor.files_size; i++) {
        file_close(&editor.files[i]);
    }
    free(editor.files);
}

#define START_COL 1

void editor_update(WINDOW* w) {
    mvwprintw(w, 1, START_COL, "EDITOR\n");

    if(editor.files_size > 0) {
        file_t* file = &editor.files[editor.active_file_idx];
        mvwprintw(w, 5, START_COL, "File: '%s'\n", file->name);

        int y = getcury(w) + 1;
        int x = START_COL;
        for(size_t i = 0; i < file->size; i++) {
            if(file->buffer[i] == '\n') {
                y++;
                x = START_COL;
                continue;
            }
            mvwprintw(w, y, x, "%c", file->buffer[i]);
            x++;
        }
    } else {
        mvwprintw(w, 5, START_COL, "ASDF: open a file using the /edit or /e command");
    }

    IF_FOCUSED(mvwprintw(w, 3, START_COL, "SELECTED\n");
                       box(w, 0, 0););

    wrefresh(w);
}

static void editor_open(const char* filename) {
    for(size_t i = 0; i < editor.files_size; i++) {
        if(strncmp(editor.files[i].name, filename, FILENAME_MAX) == 0) {
            editor.active_file_idx = i;
            return;
        }
    }

    if(editor.files_capacity <= editor.files_size) {
        editor.files_capacity *= 2;
        editor.files = realloc(editor.files, sizeof *editor.files * editor.files_capacity);
    }

    file_open(&editor.files[editor.files_size], filename);
    editor.active_file_idx = editor.files_size++;
}

void editor_receive(asdf_event_t type, const char* event) {
    if(type == ASDF_COMMAND) {
        if(strncmp(event, "/e", 2) == 0) {
            editor_open(&event[3]);
        }
    }
}