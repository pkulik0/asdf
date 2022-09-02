//
// Created by pkulik0 on 30/08/2022.
//

#ifndef ASDF_SUITE_H
#define ASDF_SUITE_H

#include "asdf.h"
#include "window/tree.h"
#include "window/dimensions.h"

#include "assert.h"
#include "stdbool.h"
#include "stdlib.h"

#define safe_assert(X) if(!(X)) return __LINE__

typedef int(*test_ptr)();

typedef struct TestGroup {
    const char* test_name;
    test_ptr test;

    struct TestGroup* next;
} test_group_t;

void run_tests(const char* group_name, test_group_t* tests);

#define TESTS_NEW(X, Y, Z) test_group_t* (X) = test_new((Y), (Z))
test_group_t* test_new(const char* test_name, test_ptr test);

#define TESTS_ADD(X, Y, Z) (X) = test_add((X), test_new((Y), (Z)))
test_group_t* test_add(test_group_t* tests, test_group_t* new);

#endif //ASDF_SUITE_H
