/*
 * Copyright (c) 2017 - Now Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include "leptunit.h"
#include "xmacro.h"
#include <assert.h>

#define GET_LIST_HEAD(l, h) h = (xlist_node_t*)(l)
#define SET_LIST_HEAD(l, h) l = (leptunit_list_t*)(h)

typedef struct __xlist_node xlist_node_t;

struct leptunit_list_t {
    xlist_node_t list;
};

void leptunit_init(leptunit_suit_t * suit)
{
    assert(suit != NULL);

    suit->count = 0;
    suit->pass = 0;
    /*
     * TODO: Check suit->tests before init it 
     */
    suit->tests = NULL;
}

void leptunit_add(leptunit_suit_t * suit, leptunit_t test)
{
    xlist_node_t *l;

    assert(suit != NULL && test != NULL);

    GET_LIST_HEAD(suit->tests, l);
    XLIST_ADD(l, test);
    SET_LIST_HEAD(suit->tests, l);
}

void leptunit_clear(leptunit_suit_t * suit)
{
    xlist_node_t *l;

    assert(suit != NULL);

    GET_LIST_HEAD(suit->tests, l);
    XLIST_FREE(l);
    SET_LIST_HEAD(suit->tests, NULL);
}

void leptunit_run(leptunit_suit_t * suit)
{
    xlist_node_t *test, *l;

    assert(suit != NULL);

    GET_LIST_HEAD(suit->tests, l);
    XLIST_FOR_EACH(test, l)
        ((leptunit_t) test->data) (suit);
}

int leptunit_summary(leptunit_suit_t * suit)
{
    assert(suit != NULL);

    int fail = suit->count - suit->pass;

    printf("total: %d, pass: %d, fail: %d, (%3.2f%%).\n", suit->count,
           suit->pass, fail, suit->pass * 100.0 / suit->count);
    return fail;
}

/* vim:set ft=c ts=4 sw=4: */
