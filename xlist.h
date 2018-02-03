/*
 * Copyright (c) 2018 - Now Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __XLIST_H__
#define __XLIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "xmacro.h"

/* define generic xmacro list */
struct __xlist_node {
    struct __xlist_node *next;
    void *data;
};

#define XLIST_NEW(l) struct __xlist_node *l = NULL

#define XLIST_ADD(l, d) do {         \
    struct __xlist_node *node;       \
    NEW0(node);                      \
    assert(node != NULL);            \
    node->data = d;                  \
    node->next = l;                  \
    l = node;                        \
} while (0)

#define XLIST_DEL(l, d) do {         \
    struct __xlist_node *node;       \
    if (l) {                         \
        node = l;                    \
        d = node->data;              \
        l = node->next;              \
        FREE(node);                  \
    }                                \
} while (0)

#define XLIST_FREE(l) do {           \
    struct __xlist_node *node;       \
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

#define XSTACK_T struct __xlist_node
#define XSTACK_NODE_T struct __xlist_node
#define XSTACK_NEW(s) XLIST_NEW(s)
#define XSTACK_PUSH(s, d) XLIST_ADD((s), (d))
#define XSTACK_POP(s, d) XLIST_DEL((s), (d))
#define XSTACK_FREE(s) XLIST_FREE(s)/* What to do */

#ifdef __cplusplus
}
#endif

#endif /* End of include guard: __XLIST_H__ */

/* vim:set ft=c ts=4 sw=4: */
