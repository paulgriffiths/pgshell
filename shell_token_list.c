#include <stdio.h>
#include <stdlib.h>
#include "shell_token_list.h"
#include "shell_token.h"
#include "std_wrappers.h"

#define INITIAL_LIST_SIZE 16

struct shell_token_list {
    struct shell_token ** tokens;
    size_t length;
    size_t capacity;
};

TokenList token_list_create(void)
{
    struct shell_token_list * new_list = xmalloc(sizeof *new_list);
    new_list->capacity = INITIAL_LIST_SIZE;
    new_list->length = 0;
    new_list->tokens = xmalloc(new_list->capacity * sizeof *new_list->tokens);
    return new_list;
}

void token_list_destroy(TokenList list)
{
    for ( size_t i = 0; i < list->length; ++i ) {
        shell_token_destroy(list->tokens[i]);
    }
    free(list->tokens);
    free(list);
}

size_t token_list_length(TokenList list)
{
    return list->length;
}

void token_list_add(TokenList list, struct shell_token * token)
{
    if ( list->length + 1 >= list->capacity ) {
        list->capacity *= 2;
        list->tokens = xrealloc(list->tokens,
                                list->capacity * sizeof *list->tokens);
    }
    list->tokens[list->length++] = token;
}

struct shell_token * token_list_token_at_index(TokenList list,
                                               const size_t index)
{
    return list->tokens[index];
}

void token_list_print(TokenList list)
{
    printf("Contents of shell token list:\n");
    for ( size_t i = 0; i < list->length; ++i ) {
        printf("  ");
        shell_token_print(token_list_token_at_index(list, i));
    }
}

