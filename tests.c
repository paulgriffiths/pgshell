#include <stdio.h>
#include "shell_token.h"
#include "shell_parser.h"

static void test_parse_input(void);

int main(void)
{
    test_parse_input();
    return 0;
}

static void test_parse_input(void)
{
    parse_input("cat with three args");
    parse_input("cat with args and trailing spaces     ");
    parse_input("cat with two \"double quoted\" args");
    parse_input("cat with two \"double quoted\" args \"two times\" over");
    parse_input("cat with two 'single quoted' args");
    parse_input("cat with two 'single quoted' args 'two times' over");
    parse_input("cat with \"single quotes 'embedded in' double quotes\"");
    parse_input("cat with 'double quotes \"embedded in\" single quotes'");
    parse_input("cat this | more that");
    parse_input("cat this<more that 'no spaces'");
    parse_input("cat this <more that 'leading space'");
    parse_input("cat this> more that 'trailing space'");
}
