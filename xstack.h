/*
 * Copyright (c) 2018 - Now Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved.
 */

#ifndef __XSTACK_H__
#define __XSTACK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "xlist.h"

#define XSTACK_T xlist_node_t
#define XSTACK_NODE_T xlist_node_t
#define XSTACK_NEW(s) XLIST_NEW(s)
#define XSTACK_PUSH(s, d) XLIST_ADD((s), (d))
#define XSTACK_POP(s, d) XLIST_DEL((s), (d))
#define XSTACK_FREE(s) XLIST_FREE(s)

#ifdef __cplusplus
}
#endif

#endif /* End of include guard: __XSTACK_H__ */

/* vim:set ft=c ts=4 sw=4: */
