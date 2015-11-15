#include <stdio.h>
#include "shell_token.h"
#include "shell_parser.h"
#include "shell_token_list.h"
#include "cmdline.h"
#include "frontend.h"

static void test_parse_input(void);

int main(void)
{
    run_shell();
    //test_parse_input();
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
        "cat this> more that 'trailing space'",
        "cat this that|more and everything else"
    };

    for ( size_t i = 0; i < sizeof(cmds) / sizeof(cmds[0]); ++i ) {
        printf("--------------------\n");
        TokenList list = parse_input(cmds[i]);
        CmdCmpList cmds = cmdline_create(list);
        token_list_destroy(list);
        cmdline_print(cmds);
        cmdline_destroy(cmds);
    }
}
