# LeptUnit

[![Build Status](https://travis-ci.org/ishbguy/leptunit.svg?branch=master)](https://travis-ci.org/ishbguy/leptunit) [![codecov](https://codecov.io/gh/ishbguy/leptunit/branch/master/graph/badge.svg)](https://codecov.io/gh/ishbguy/leptunit)

LeptUnit is a light weight C unit test library which is inspired by [miloyip](https://github.com/moliyip)'s [json-tutorial](https://github.com/moliyip/json-tutorial).

## Features

+ Basic type test, such as: int, double, str, ptr
+ Simple usage
+ No dependency
+ ANSI C

## Installation

### Without build tool, only make
In Linux with gcc, make:

```
$ cd /path/to/leptunit
$ make
```
This make will generate `libleptunit.so` and `test-leptunit`, `libleptunit.so` is the dynamic shared library, `test-leptunit` is a simple test for leptunit. If you just want to generate one of it you can do like this:
```
$ cd /path/to/leptunit
$ make lib
```
or
```
$ cd /path/to/leptunit
$ make test
```

### With cmake build tool

```
$ mkdir build
$ cd build
$ cmake ..
```
**Don't run `cmake` in the repo root directory for it will generate a new Makefile to over-write the repo's default Makefile!**

## Configuration

After generate the dynamic shared library, you can copy it to the standard library directory in Linux, or:
```
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/could/ld/find
```

## Usage

Write test.c:

```C
#include "/path/to/leptunit.h"

/* test_case's arg must be "leptunit_suit *suit" !!!*/
void test_case(leptunit_suit *suit) {
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

int main(int argc, char *argv[])
{
    leptunit_suit_t *suit = leptunit_new() ;
    leptunit_add(suit, test_leptunit_summary);
    leptunit_add(suit, test_leptunit_expect);
    leptunit_run(suit);
    leptunit_summary(suit);
    leptunit_free(&suit);
    return 0;
}
```

Then compile it like this:
```
$ gcc -lm -lleptunit -L/path/to/leptunit/dynamic/lib -o test test.c
$ ./test
```

If you use `EXPECT_EQ_DOUBLE`, `EXPECT_NE_DOUBLE`, `EXPECT_EQ_DOUBLE_PREC` and `EXPECT_NE_DOUBLE_PREC`, you must compile you test with -lm option.

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

## Authors

+ [ishbguy](https://github.com/ishbguy)

## License

For public used.
