#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "shell_parser.h"
#include "std_wrappers.h"
#include "shell_token_list.h"

/*  TODO: Modify to handle unbalanced quotation marks.
 *  TODO: Modify to handle escape characters.
 */

enum quote_type {
    QUOTE_SINGLE,
    QUOTE_DOUBLE
};

static bool is_operator(const char c)
{
    static const char operators[] = "|<>";
    static const size_t num_ops = sizeof(operators) / sizeof(operators[0]) - 1;

    for ( size_t i = 0; i < num_ops; ++i ) {
        if ( c == operators[i] ) {
            return true;
        }
    }

    return false;
}

TokenList parse_input(const char * input)
{
    char * buffer = xmalloc(strlen(input) + 1);
    TokenList list = token_list_create();
    struct shell_token * token = NULL;
    size_t i_idx = 0;
    size_t b_idx = 0;
    bool quoted = false;
    enum quote_type quote_type;

    while ( input[i_idx] ) {
        b_idx = 0;
        token = NULL;

        while ( input[i_idx] && isspace(input[i_idx]) ) {
            ++i_idx;
        }

        if ( input[i_idx] && is_operator(input[i_idx]) ) {
            switch ( input[i_idx] ) {
                case '|':
                    token = operator_token_create(SOT_PIPE);
                    break;

                case '<':
                    token = operator_token_create(SOT_REDIRECT_LEFT);
                    break; 

                case '>':
                    token = operator_token_create(SOT_REDIRECT_RIGHT);
                    break;

                default:
                    printf("Aborting due to unrecognized token: '%c'\n",
                           input[i_idx]);
                    abort();
                    break;
            }
            buffer[b_idx++] = input[i_idx++];
        }
        else while ( input[i_idx] && (!isspace(input[i_idx]) || quoted) ) {
            if ( input[i_idx] == '"' ) {
                if ( quoted && quote_type == QUOTE_DOUBLE ) {
                    quoted = false;
                    ++i_idx;
                    continue;
                }
                else if ( !quoted ) {
                    quoted = true;
                    quote_type = QUOTE_DOUBLE;
                    ++i_idx;
                    continue;
                }
            }

            if ( input[i_idx] == '\'' ) {
                if ( quoted && quote_type == QUOTE_SINGLE ) {
                    quoted = false;
                    ++i_idx;
                    continue;
                }
                else if ( !quoted ) {
                    quoted = true;
                    quote_type = QUOTE_SINGLE;
                    ++i_idx;
                    continue;
                }
            }

            if ( !quoted && is_operator(input[i_idx]) ) {
                break;
            }

            buffer[b_idx++] = input[i_idx++];
        }

        if ( b_idx != 0 && !token ) {
            buffer[b_idx++] = '\0';
            token = string_token_create(buffer);
        }

        if ( token ) {
            token_list_add(list, token);
        }
    }

    free(buffer);

    return list;
}
