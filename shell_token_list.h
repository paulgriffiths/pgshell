#ifndef PG_SHELL_SHELL_TOKEN_LIST_H
#define PG_SHELL_SHELL_TOKEN_LIST_H

#include <stddef.h>
#include "shell_token.h"

typedef struct shell_token_list * TokenList;

TokenList token_list_create(void);
void token_list_destroy(TokenList list);
size_t token_list_length(TokenList list);
void token_list_add(TokenList list, struct shell_token * token);
struct shell_token * token_list_token_at_index(TokenList list,
                                               const size_t index);
void token_list_print(TokenList list);

#endif      /*  PG_SHELL_SHELL_TOKEN_LIST_H  */
