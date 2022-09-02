//
// Created by pkulik0 on 31/08/2022.
//

#include "file.h"

// TODO: handle errors
int file_open(file_t* file, const char* filename) {
    size_t filename_len = strnlen(filename, FILENAME_MAX);
    memcpy(file->name, filename, filename_len);

    file->stream = fopen(filename, "a+");

    fseek(file->stream, 0, SEEK_END);
    file->size = ftell(file->stream);
    file->capacity = file->size * 2;
    rewind(file->stream);

    file->buffer = malloc(file->capacity);
//    file->buffer[file->size] = '\0';
    fread(file->buffer, file->size, 1, file->stream);

    match_filetype(file);
    return 0;
}

void file_close(file_t* file) {
    fclose(file->stream);
    free(file->name);
    free(file->buffer);
}

void match_filetype(file_t* file) {
    file->type = FILE_TEXT;
}