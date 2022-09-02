//
// Created by pkulik0 on 31/08/2022.
//

#ifndef ASDF_FILE_H
#define ASDF_FILE_H

#include "stdio.h"
#include "stdlib.h"
#include "sys/stat.h"
#include "string.h"

#define MAX_LENGTH 4096

typedef enum FileType {
    FILE_TEXT, FILE_C, FILE_PYTHON, FILE_HTML, FILE_CSS, FILE_JAVASCRIPT
} filetype_t;

typedef struct File {
    FILE* stream;
    char* name;
    filetype_t type;
    char* buffer;

    size_t capacity;
    size_t size;
} file_t;


file_t file_open(const char* filename);
void file_close(file_t* file);

void match_filetype(file_t* file);

#endif //ASDF_FILE_H
