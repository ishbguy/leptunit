/*
 * Copyright (c) 2017 - Now Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#include "leptunit.h"

void test_leptunit_expect(leptunit_suit_t * suit)
{
    /*
     * Test bool 
     */
    EXPECT_TRUE(1);
    EXPECT_FLASE(0);

    /*
     * Test equal 
     */
    EXPECT_EQ_INT(1, 1);
    EXPECT_EQ_DOUBLE(1.0, 1.0);
    EXPECT_EQ_DOUBLE_PREC(1.0, 1.0, 0.000001);
    EXPECT_EQ_STR("leptunit", "leptunit");
    EXPECT_EQ_NSTR("leptunit", "leptunit", strlen("leptunit"));
    EXPECT_EQ_PTR("leptunit", "leptunit");
    EXPECT_EQ_NULL(NULL);

    /*
     * Test not equal 
     */
    EXPECT_NE_INT(1, 2);
    EXPECT_NE_DOUBLE(1.0, 2.0);
    EXPECT_NE_DOUBLE_PREC(1.0, 2.0, 0.000001);
    EXPECT_NE_STR("leptunit", "leptunit.h");
    EXPECT_NE_NSTR("leptunit", "hello world", strlen("leptunit"));
    EXPECT_NE_PTR("leptunit", "hello world");
    EXPECT_NE_NULL("leptunit");
}

void test_leptunit_summary(leptunit_suit_t * suit)
{
    EXPECT_EQ_INT(0, leptunit_summary(suit));
}

int main(int argc, char *argv[])
{
    leptunit_suit_t suit;

    leptunit_init(&suit);
    leptunit_add(&suit, test_leptunit_summary);
    leptunit_add(&suit, test_leptunit_expect);
    leptunit_run(&suit);
    leptunit_summary(&suit);
    leptunit_clear(&suit);
    return 0;
}

/* vim:set ft=c ts=4 sw=4: */
