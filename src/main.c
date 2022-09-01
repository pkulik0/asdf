#include "asdf.h"
#include "scripts.h"

int main(int argc, char** argv) {
    scripts_run(argv[0]);
    return 0;
    asdf_init();
    asdf_run();
    asdf_destroy();
    return 0;
}