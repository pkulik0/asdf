//
// Created by pkulik0 on 01/09/2022.
//

#include "editor.h"

static editor_t editor;

void editor_init() {
    editor.relative_line_num = false;
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

#define START_COL 3

static void editor_print_file(WINDOW* w) {
    size_t offset = editor.files[editor.active_file_idx].line_offset;
    file_t* file = &editor.files[editor.active_file_idx].file;
    mvwprintw(w, 0, START_COL, file->name);

    int y = getcury(w) + 1;
    int x = START_COL;
    int max_y = getmaxy(w)-1;

    for(size_t i = 0; i < file->size && y < max_y; i++) {
        if(file->buffer[i] == '\n') {
            if(offset == 0) { y++; } else { offset--; }
            x = START_COL;
            continue;
        }
        if(offset > 0) continue;

        mvwprintw(w, y, x, "%c", file->buffer[i]);
        x++;
    }
}

void editor_update(WINDOW* w) {
    IF_FOCUSED(box(w, 0, 0););

    if(editor.files_size > 0) {
        editor_print_file(w);
    } else {
        mvwprintw(w, 5, START_COL, "ASDF: open a file using /edit <path> or /e <path>");
    }

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

    size_t* idx = &editor.files_size;
    file_open(&editor.files[*idx].file, filename);
    editor.files[*idx].line_offset = 0;
    editor.active_file_idx = (*idx)++;

}

void editor_receive(asdf_event_t type, const char* event) {
    if(type == ASDF_COMMAND) {
        if(strncmp(event, "/e", 2) == 0) {
            editor_open(&event[3]);
        }
    }
}