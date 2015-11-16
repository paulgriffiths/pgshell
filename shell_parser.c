#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "shell_parser.h"
#include "std_wrappers.h"
#include "shell_token_list.h"

/*
 *  TODO: Modify to handle unbalanced quotation marks.
 *  TODO: Modify to handle escape characters.
 */

enum quote_type {
    QUOTE_SINGLE,
    QUOTE_DOUBLE
};

static bool is_operator(const char c);

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

        /*  Skip leading whitespace  */

        while ( input[i_idx] && isspace(input[i_idx]) ) {
            ++i_idx;
        }

        /*  Check first for an operator, then for a string  */

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

            /*  Deal with double quote characters  */

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

            /*  Deal with single quote characters  */

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

            /*  No need for space between a string and an
             *  operator, so end this token if we find the
             *  latter.
             */

            if ( !quoted && is_operator(input[i_idx]) ) {
                break;
            }

            /*  Otherwise add current character to buffer  */

            buffer[b_idx++] = input[i_idx++];
        }

        /*  Create a string token if we have a non-empty buffer  */

        if ( b_idx != 0 && !token ) {
            buffer[b_idx++] = '\0';
            token = string_token_create(buffer);
        }

        /*  Add either the string token we just created, or the
         *  operator token we created earlier, to the token list,
         *  if we created a token.
         */

        if ( token ) {
            token_list_add(list, token);
        }
    }

    free(buffer);
    return list;
}

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
