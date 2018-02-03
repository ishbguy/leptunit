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

typedef struct {
    leptunit_t test;
    char *test_name;
} leptunit_node_t;

struct leptunit_list_t {
    xlist_node_t list;
};

struct leptunit_suit_t {
    int count;
    int pass;
    int fail;
    leptunit_list_t *tests;
};

static leptunit_node_t *leptunit_node_new(leptunit_t test,
                                          const char *test_name)
{
    leptunit_node_t *node;

    assert(test != NULL && test_name != NULL);

    MALLOC(node, sizeof(leptunit_node_t));
    assert(node != NULL);
    node->test = test;
    MALLOC(node->test_name, strlen(test_name) + 1);
    strcpy(node->test_name, test_name);
    return node;
}

static void leptunit_node_free(leptunit_node_t ** node)
{
    assert(node != NULL);

    if (*node) {
        FREE((*node)->test_name);
        FREE(*node);
    }
}

leptunit_suit_t *leptunit_new(void)
{
    leptunit_suit_t *suit;

    MALLOC(suit, sizeof(leptunit_suit_t));
    assert(suit != NULL);
    suit->count = 0;
    suit->pass = 0;
    suit->tests = NULL;
    return suit;
}

void leptunit_free(leptunit_suit_t ** suit)
{
    assert(suit != NULL);

    if (*suit) {
        xlist_node_t *test, *list;

        GET_LIST_HEAD((*suit)->tests, list);
        XLIST_FOR_EACH(test, list)
            leptunit_node_free((leptunit_node_t **) (&test->data));
        XLIST_FREE(list);
        SET_LIST_HEAD((*suit)->tests, NULL);
        FREE(*suit);
    }
}

void __leptunit_add(leptunit_suit_t * suit, leptunit_t test,
                    const char *test_name)
{
    xlist_node_t *list;

    assert(suit != NULL && test != NULL && test_name != NULL);

    GET_LIST_HEAD(suit->tests, list);
    XLIST_ADD(list, leptunit_node_new(test, test_name));
    SET_LIST_HEAD(suit->tests, list);
}

void leptunit_set_fail(leptunit_suit_t * suit)
{
    assert(suit != NULL);
    suit->fail = 1;
}

void leptunit_clear_fail(leptunit_suit_t * suit)
{
    assert(suit != NULL);
    suit->fail = 0;
}

static int leptunit_is_fail(leptunit_suit_t * suit)
{
    return suit->fail ? 1 : 0;
}

static void run_test_and_print_result(leptunit_suit_t * suit,
                                      xlist_node_t * test)
{
    leptunit_node_t *node = (leptunit_node_t *) test->data;

    ((leptunit_t) node->test) (suit);

    printf("%-30s %s\n", node->test_name,
           leptunit_is_fail(suit) ? "Not OK" : "OK");
    leptunit_clear_fail(suit);
}

void leptunit_run(leptunit_suit_t * suit)
{
    xlist_node_t *test, *list;

    assert(suit != NULL);

    GET_LIST_HEAD(suit->tests, list);
    XLIST_FOR_EACH(test, list)
        run_test_and_print_result(suit, test);
}

void leptunit_count(leptunit_suit_t * suit)
{
    assert(suit != NULL);
    suit->count++;
}

void leptunit_pass(leptunit_suit_t * suit)
{
    assert(suit != NULL);
    suit->pass++;
}

int leptunit_summary(leptunit_suit_t * suit)
{
    int fail;

    assert(suit != NULL);

    fail = suit->count - suit->pass;
    printf("total: %d, pass: %d, fail: %d, (%3.2f%%).\n", suit->count,
           suit->pass, fail, suit->pass * 100.0 / suit->count);
    return fail;
}

/* vim:set ft=c ts=4 sw=4: */
