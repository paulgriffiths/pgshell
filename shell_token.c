#include <stdio.h>
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

struct shell_token * operator_token_create(const enum shell_operator_type type)
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

void shell_token_print(struct shell_token * token)
{
    switch ( token->type ) {
        case STT_STRING:
            printf("String token: %s\n", token->content.str);
            break;

        case STT_OPERATOR:
            switch ( token->content.operator ) {
                case SOT_PIPE:
                    printf("Operator token: PIPE\n");
                    break;

                case SOT_REDIRECT_LEFT:
                    printf("Operator token: REDIRECT LEFT\n");
                    break;

                case SOT_REDIRECT_RIGHT:
                    printf("Operator token: REDIRECT RIGHT\n");
                    break;

                default:
                    printf("Operator token: UNRECOGNIZED\n");
                    break;
            }
    }
}

void operator_print(const enum shell_operator_type type)
{
    switch ( type ) {
        case SOT_PIPE:
            printf("Operator: PIPE\n");
            break;

        case SOT_REDIRECT_LEFT:
            printf("Operator: REDIRECT LEFT\n");
            break;

        case SOT_REDIRECT_RIGHT:
            printf("Operator: REDIRECT RIGHT\n");
            break;

        default:
            printf("Operator: UNRECOGNIZED\n");
            break;
    }
}
