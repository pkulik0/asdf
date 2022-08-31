//
// Created by pkulik0 on 30/08/2022.
//

#include "suite.h"

static int test_dimensions() {
    dimensions_t dim = (dimensions_t){3, 5};
    safe_assert(dim.x == 3 && dim.y == 5);
    return 0;
}

static int test_dimensions2() {
    dimensions_t dim = (dimensions_t){-1, -2};
    safe_assert(dim.x == -1 && dim.y == -2);
    return 0;
}

static bool on_update_run = false;
void on_update(WINDOW* w) {
    on_update_run = true;
};

static int test_tree() {
    tree_t* tree = tree_root(tree_leaf(on_update));
    safe_assert(tree->content == LEAF);
    safe_assert(tree->leaf.on_update == on_update);

    on_update_run = false;
    tree_update(tree);
    safe_assert(on_update_run);

    return 0;
}

int main() {
    TESTS_NEW(group, "dim1", test_dimensions);
    TESTS_ADD(group, "dim2", test_dimensions2);
    TESTS_ADD(group, "tree1", test_tree);
    run_tests("main", group);

    return 0;
}
