#include "asdf.h"
#include "scripts.h"
#include "file.h"

int main(int argc, char** argv) {
    scripts_run(argv[0]);
    if(argc > 1) {
        file_t file = file_open(argv[1]);
        printf("content:\n\n'%s'\n", file.buffer);
        file_close(&file);
        printf("done\n");
    } else {
        printf("Usage:\n%s <filename>\n", argv[0]);
    }
    return 0;
    asdf_init();
    asdf_run();
    asdf_destroy();
    return 0;
}