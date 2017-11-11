/*
 * Copyright (c) 2017 - Now Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include "leptunit.h"

void leptunit_init(leptunit_suit_t * suit)
{
    suit->count = 0;
    suit->pass = 0;
}

void leptunit_run(leptunit_suit_t * suit, leptunit_t * tests)
{
    for (int i = 0; tests[i] != NULL; i++)
        tests[i] (suit);
}

int leptunit_summary(leptunit_suit_t * suit)
{
    int fail = suit->count - suit->pass;

    printf("total: %d, pass: %d, fail: %d, (%3.2f%%).\n", suit->count,
           suit->pass, fail, suit->pass * 100.0 / suit->count);
    return fail;
}

/* vim:set ft=c ts=4 sw=4: */
