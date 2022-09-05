//
// Created by pkulik0 on 01/09/2022.
//

#ifndef ASDF_EDITOR_H
#define ASDF_EDITOR_H

#include "ncurses.h"
#include "asdf.h"
#include "file.h"
#include "window/dimensions.h"

typedef struct FileInfo {
    file_t file;
    size_t line_offset;

    struct Cursor {
        dimensions_t screen;
        char* buffer;
    } cursor;
} file_info_t;

typedef struct Editor {
    file_info_t* files;
    size_t files_capacity;
    size_t files_size;

    size_t active_file_idx;

    bool is_input_mode;
    bool relative_line_num;
} editor_t;

void editor_init();
void editor_destroy();

void editor_update(WINDOW* window);
void editor_handle_key(int key);
void editor_handle_command(const char* command);

#endif //ASDF_EDITOR_H
