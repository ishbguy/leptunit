/*
 * Copyright (c) 2018 - Now Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __XLIST_H__
#define __XLIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "xalloc.h"

/* define generic xmacro list */
typedef struct xlist_node {
    struct xlist_node *next;
    void *data;
} xlist_node_t, xlist_t;

#define XLIST_NEW(l) xlist_node_t *l = NULL

#define XLIST_ADD(l, d) do {         \
    xlist_node_t *node;              \
    NEW0(node);                      \
    assert(node != NULL);            \
    node->data = d;                  \
    node->next = l;                  \
    l = node;                        \
} while (0)

#define XLIST_DEL(l, d) do {         \
    xlist_node_t *node;              \
    if (l) {                         \
        node = l;                    \
        d = node->data;              \
        l = node->next;              \
        FREE(node);                  \
    }                                \
} while (0)

#define XLIST_FREE(l) do {           \
    xlist_node_t *node;              \
    while (l) {                      \
        node = l;                    \
        l = node->next;              \
        free(node);                  \
    }                                \
} while (0)

#define XLIST_FOR_EACH(n, l)         \
    for (n = l; n; n = n->next)
#define XLIST_FOR_EACH_SAFE(n, s, l) \
    for (n = l; n? s = n->next, n: n; n = s)

#ifdef __cplusplus
}
#endif

#endif /* End of include guard: __XLIST_H__ */

/* vim:set ft=c ts=4 sw=4: */
