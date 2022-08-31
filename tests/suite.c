//
// Created by pkulik0 on 30/08/2022.
//

#include "suite.h"

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

test_group_t* test_new(const char* test_name, test_ptr test) {
    test_group_t* group = malloc(sizeof *group);

    group->test_name = test_name;
    group->test = test;
    group->next = NULL;

    return group;
}

test_group_t* test_add(test_group_t* tests, test_group_t* new) {
    if(!tests || !new) return NULL;

    new->next = tests;
    return new;
}