//
// Created by pkulik0 on 31/08/2022.
//

#ifndef ASDF_FILE_H
#define ASDF_FILE_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef enum FileType {
    FILE_TEXT,
    FILE_C,
    FILE_PYTHON,
    FILE_HTML,
    FILE_CSS,
    FILE_JAVASCRIPT,
} filetype_t;

//const char* const FILETYPE_TABLE[] = {
//        "Text",
//        "C/C++",
//        "Python",
//        "HTML",
//        "CSS",
//        "JavaScript",
//};

typedef struct File {
    FILE* stream;
    char name[FILENAME_MAX];
    filetype_t type;
    char* buffer;

    size_t capacity;
    size_t size;
} file_t;

int file_open(file_t* file, const char* filename);
int file_save(file_t* file);
void file_close(file_t* file);

void match_filetype(file_t* file);

#endif //ASDF_FILE_H
