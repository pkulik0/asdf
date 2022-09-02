//
// Created by pkulik0 on 29/08/2022.
//

#ifndef ASDF_ASDF_H
#define ASDF_ASDF_H

#include "window/tree.h"

typedef struct Asdf {
    tree_t* root;
    leaf_t* focused_leaf;
} asdf_t;

typedef enum AsdfEvent {
    ASDF_KEY,
    ASDF_COMMAND
} asdf_event_t;

asdf_t asdf;

void asdf_init();
void asdf_run();
void asdf_destroy();

#define IF_FOCUSED(X) if(asdf.focused_leaf) \
                        if(asdf.focused_leaf->window == w) \
                            { X }

// Skip default ncurses colors
#define Color(X) ((int)(X)+8)

#endif //ASDF_ASDF_H
