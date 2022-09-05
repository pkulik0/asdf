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

#define TESTS_NEW(X, Y, Z) test_group_t* (X) = test_new((Y), (Z))
test_group_t* test_new(const char* test_name, test_ptr test) {
    test_group_t* group = malloc(sizeof *group);

    group->test_name = test_name;
    group->test = test;
    group->next = NULL;

    return group;
}

#define TESTS_ADD(X, Y, Z) (X) = test_add((X), test_new((Y), (Z)))
test_group_t* test_add(test_group_t* tests, test_group_t* new) {
    if(!tests || !new) return NULL;

    new->next = tests;
    return new;
}

void run_tests(const char* group_name, test_group_t* tests) {
    int count = 0;
    int failed = 0;

    printf("Testing group %s\n", group_name);

    while(tests) {
        printf("Test #%d \t%s\t", count++, tests->test_name);

        int line = tests->test();
        if(line == 0) {
            printf("[SUCCESS]\n");
        } else {
            printf("[FAILURE] (line %d)\n", line);
            failed++;
        }

        tests = tests->next;
    }

    printf("Group finished running.\n");

    if(failed)
        printf("%d out of %d tests failed.\n", failed, count);
    else
        printf("All %d tests passed.", count);
}

#endif //ASDF_SUITE_H
