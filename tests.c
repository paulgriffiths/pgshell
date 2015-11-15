#include <stdio.h>
#include "shell_token.h"
#include "shell_parser.h"
#include "shell_token_list.h"

static void test_parse_input(void);

int main(void)
{
    test_parse_input();
    return 0;
}

static void test_parse_input(void)
{
    static char * cmds[] = {
        "cat with three args",
        "cat with args and trailing spaces     ",
        "cat with two \"double quoted\" args",
        "cat with two \"double quoted\" args \"two times\" over",
        "cat with two 'single quoted' args",
        "cat with two 'single quoted' args 'two times' over",
        "cat with \"single quotes 'embedded in' double quotes\"",
        "cat with 'double quotes \"embedded in\" single quotes'",
        "cat this | more that",
        "cat this<more that 'no spaces'",
        "cat this <more that 'leading space'",
        "cat this> more that 'trailing space'"
    };

    TokenList list;
    for ( size_t i = 0; i < sizeof(cmds) / sizeof(cmds[0]); ++i ) {
        list = parse_input(cmds[i]);
        token_list_print(list);
        token_list_destroy(list);
    }
}
