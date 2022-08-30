//
// Created by pkulik0 on 29/08/2022.
//

#ifndef ASDF_ASDF_H
#define ASDF_ASDF_H

// Skip default ncurses colors
#define Color(X) (int)(X)+8

void asdf_init();
void asdf_run();
void asdf_destroy();

#endif //ASDF_ASDF_H
