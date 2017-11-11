/*
 * Copyright (c) 2017 - Now Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include "leptunit.h"
#include "xmacro.h"
#include <assert.h>

typedef struct __xlist_node xlist_node_t;

struct leptunit_list_t {
    xlist_node_t list;
};

void leptunit_init(leptunit_suit_t * suit)
{
    assert(suit);
    suit->count = 0;
    suit->pass = 0;
    suit->tests = NULL;
}

void leptunit_add(leptunit_suit_t * suit, leptunit_t test)
{
    assert(suit && test);

    xlist_node_t *l = (xlist_node_t *) suit->tests;

    XLIST_ADD(l, test);
    suit->tests = (leptunit_list_t *) l;
}

void leptunit_clear(leptunit_suit_t * suit)
{
    assert(suit);

    xlist_node_t *l = (xlist_node_t *) suit->tests;

    XLIST_FREE(l);
    suit->tests = NULL;
}

void leptunit_run(leptunit_suit_t * suit)
{
    assert(suit);

    xlist_node_t *test;
    xlist_node_t *l = (xlist_node_t *) suit->tests;

    XLIST_FOR_EACH(test, l)
        ((leptunit_t) test->data) (suit);
}

int leptunit_summary(leptunit_suit_t * suit)
{
    assert(suit);
    int fail = suit->count - suit->pass;

    printf("total: %d, pass: %d, fail: %d, (%3.2f%%).\n", suit->count,
           suit->pass, fail, suit->pass * 100.0 / suit->count);
    return fail;
}

/* vim:set ft=c ts=4 sw=4: */
