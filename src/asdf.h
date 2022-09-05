//
// Created by pkulik0 on 29/08/2022.
//

#ifndef ASDF_ASDF_H
#define ASDF_ASDF_H

#include "window/tree.h"

typedef struct Asdf {
    tree_t* root;
    tree_t* focused;

    dimensions_t size;
} asdf_t;

asdf_t asdf;

void asdf_init();
void asdf_run();
void asdf_destroy();

#define IF_FOCUSED(X) if(asdf.focused) \
                        if(asdf.focused->leaf.window == w) \
                            { X }

// Skip default ncurses colors
#define Color(X) ((int)(X)+8)

#endif //ASDF_ASDF_H
