#include <stdlib.h>
#include "shell_token.h"
#include "std_wrappers.h"

struct shell_token * string_token_create(const char * str)
{
    struct shell_token * new_token = xmalloc(sizeof *new_token);
    new_token->type = STT_STRING;
    new_token->content.str = xstrdup(str);
    return new_token;
}

struct shell_token * operator_token_create(enum shell_operator_type type)
{
    struct shell_token * new_token = xmalloc(sizeof *new_token);
    new_token->type = STT_OPERATOR;
    new_token->content.operator = type;
    return new_token;
}

void shell_token_destroy(struct shell_token * token)
{
    if ( token->type == STT_STRING ) {
        free(token->content.str);
    }
    free(token);
}

