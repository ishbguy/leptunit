/*
 * Copyright (c) 2017 - Now Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include "leptunit.h"

int leptunit_main_ret = 0;
int leptunit_count = 0;
int leptunit_pass = 0;
int leptunit_fail = 0;

static void run_test(leptunit_t test)
{
    test();
}

void leptunit_run(leptunit_t * tests)
{
    for (int i = 0; tests[i] != NULL; i++)
        run_test(tests[i]);
}

int leptunit_summary(void)
{
    printf("total: %d, pass: %d, fail: %d, (%3.2f%%).\n", leptunit_count,
           leptunit_pass, leptunit_fail,
           leptunit_pass * 100.0 / leptunit_count);
    return leptunit_main_ret;
}

/* vim:set ft=c ts=4 sw=4: */
