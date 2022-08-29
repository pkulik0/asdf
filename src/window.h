//
// Created by pkulik0 on 29/08/2022.
//

#ifndef ASDF_WINDOW_H
#define ASDF_WINDOW_H

#include "dimensions.h"

typedef struct Window {
    dimensions_t dimensions;
} window_t;

void window_destroy(window_t* window_ptr);

#endif //ASDF_WINDOW_H
