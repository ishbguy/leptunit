/*
 * Copyright (c) 2017 - Now Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __LEPTUNIT_H__
#define __LEPTUNIT_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/* these EXPECT macros must use in a test case */
#define EXPECT_EQ_BASE(equality, expect, actual, format)                      \
    do {                                                                      \
        if (equality)                                                         \
            suit->pass++;                                                     \
        else                                                                  \
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", \
                    __FILE__, __LINE__, expect, actual);                      \
        suit->count++;                                                        \
    } while(0)

/* equal */
#define EXPECT_TRUE(expr)                                                     \
    EXPECT_EQ_BASE((expr) != 0, #expr " true", "false", "%s")

#define EXPECT_FLASE(expr)                                                    \
    EXPECT_EQ_BASE((expr) == 0, #expr " false", "true", "%s")

#define EXPECT_EQ_INT(expect, actual)                                         \
    EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

/* compare two double which are not calculate result */
#define EXPECT_EQ_DOUBLE(expect, actual)                                      \
    EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%.17g")

#define EXPECT_EQ_DOUBLE_PREC(expect, actual, prec)                           \
    EXPECT_EQ_BASE((fabs((expect) - (actual)) < fabs(prec)),                  \
            expect, actual, "%.17g")

#define EXPECT_EQ_STR(expect, actual)                                         \
    EXPECT_EQ_BASE((!strcmp((expect), (char *)(actual))),                     \
            expect, (char *)actual, "%s")

#define EXPECT_EQ_NSTR(expect, actual, length)                                \
    EXPECT_EQ_BASE((!strncmp((expect), (char *)(actual), length)),            \
            expect, (char *)actual, "%s")

#define EXPECT_EQ_PTR(expect, actual)                                         \
    EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%p")

#define EXPECT_EQ_NULL(actual)                                                \
    EXPECT_EQ_BASE((NULL) == (actual), NULL, actual, "%p")

/* not equal */
#define EXPECT_NE_INT(expect, actual)                                         \
    EXPECT_EQ_BASE((expect) != (actual), expect, actual, "%d")

#define EXPECT_NE_DOUBLE(expect, actual)                                      \
    EXPECT_EQ_BASE((expect) != (actual), expect, actual, "%.17g")

#define EXPECT_NE_DOUBLE_PREC(expect, actual, prec)                           \
    EXPECT_EQ_BASE((fabs((expect) - (actual)) > fabs(prec)),                  \
            expect, actual, "%.17g")

#define EXPECT_NE_STR(expect, actual)                                         \
    EXPECT_EQ_BASE((strcmp((expect), (char *)(actual))),                      \
            expect, (char *)actual, "%s")

#define EXPECT_NE_NSTR(expect, actual, length)                                \
    EXPECT_EQ_BASE((strncmp((expect), (char *)(actual), length)),             \
            expect, (char *)actual, "%s")

#define EXPECT_NE_PTR(expect, actual)                                         \
    EXPECT_EQ_BASE((expect) != (actual), expect, actual, "%p")

#define EXPECT_NE_NULL(actual)                                                \
    EXPECT_EQ_BASE((NULL) != (actual), NULL, actual, "%p")

typedef struct leptunit_list_t leptunit_list_t;

/* test suit type */
typedef struct {
    int count;
    int pass;
    leptunit_list_t *tests;
} leptunit_suit_t;

/* test case type */
typedef void (*leptunit_t) (leptunit_suit_t * suit);

/* init a test suit */
extern void leptunit_init(leptunit_suit_t * suit);

/* add test case to test suit */
extern void leptunit_add(leptunit_suit_t *suit, leptunit_t test);

/* clear all test cases in test suit */
extern void leptunit_clear(leptunit_suit_t *suit);

/* run a test suit */
extern void leptunit_run(leptunit_suit_t * suit);

/* print out unit tests summary */
extern int leptunit_summary(leptunit_suit_t * suit);

#endif /* End of include guard: __LEPTUNIT_H__ */

/* vim:set ft=c ts=4 sw=4: */
