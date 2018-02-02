/*
 * Copyright (c) 2017 - Now Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __LEPTUNIT_H__
#define __LEPTUNIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "lepttypes.h"

/* these EXPECT macros must use in a test case */
#define EXPECT_EQ_BASE(equality, expect, actual, format)                      \
    do {                                                                      \
        if (equality)                                                         \
            leptunit_pass(suit);                                              \
        else {                                                                \
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", \
                    __FILE__, __LINE__, expect, actual);                      \
            leptunit_set_fail(suit);                                          \
        }                                                                     \
        leptunit_count(suit);                                                 \
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
    EXPECT_EQ_BASE((strcmp((expect), (char *)(actual)) == 0),                 \
            expect, (char *)actual, "%s")

#define EXPECT_EQ_NSTR(expect, actual, length)                                \
    EXPECT_EQ_BASE((strncmp((expect), (char *)(actual), length) == 0),        \
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
    EXPECT_EQ_BASE((strcmp((expect), (char *)(actual)) != 0),                 \
            expect, (char *)actual, "%s")

#define EXPECT_NE_NSTR(expect, actual, length)                                \
    EXPECT_EQ_BASE((strncmp((expect), (char *)(actual), length) != 0),        \
            expect, (char *)actual, "%s")

#define EXPECT_NE_PTR(expect, actual)                                         \
    EXPECT_EQ_BASE((expect) != (actual), expect, actual, "%p")

#define EXPECT_NE_NULL(actual)                                                \
    EXPECT_EQ_BASE((NULL) != (actual), NULL, actual, "%p")

typedef struct leptunit_list_t leptunit_list_t;
typedef struct leptunit_suit_t leptunit_suit_t;
typedef void (*leptunit_t) (leptunit_suit_t * suit);
#define LEPTUNIT_TEST_CASE(test) void (test)(leptunit_suit_t * suit)

LEPT_API leptunit_suit_t *leptunit_new(void);
LEPT_API void leptunit_free(leptunit_suit_t **suit);
LEPT_API void __leptunit_add(leptunit_suit_t *suit, leptunit_t test, const char *test_name);
#define leptunit_add(suit, test) __leptunit_add(suit, test, #test)
LEPT_API void leptunit_run(leptunit_suit_t * suit);
LEPT_API void leptunit_count(leptunit_suit_t *suit);
LEPT_API void leptunit_pass(leptunit_suit_t *suit);
LEPT_API void leptunit_set_fail(leptunit_suit_t *suit);
LEPT_API void leptunit_clear_fail(leptunit_suit_t *suit);
LEPT_API int leptunit_summary(leptunit_suit_t * suit);

#ifdef __cplusplus
}
#endif

#endif /* End of include guard: __LEPTUNIT_H__ */

/* vim:set ft=c ts=4 sw=4: */
