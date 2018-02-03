/*
 * Copyright (c) 2018 - Now Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __XALLOC_H__
#define __XALLOC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>

/* memory allocated functions macros. */
#define MALLOC(ptr, size) ptr = malloc(size)
#define CALLOC(ptr, num, size) ptr = calloc(num, size)
#define REALLOC(ptr, size) ptr = realloc(ptr, size)
#define STRDUP(dest, src) dest = strdup(src)
#define NEW(ptr) ptr = malloc(sizeof(*(ptr)))
#define NEW0(ptr) ptr = calloc(1, sizeof(*(ptr)))
#define FREE(ptr) free((ptr)), ptr = NULL

#ifdef __cplusplus
}
#endif

#endif /* End of include guard: __XALLOC_H__ */

/* vim:set ft=c ts=4 sw=4: */
