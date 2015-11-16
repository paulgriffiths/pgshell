#include <stdio.h>
#include <stdlib.h>
#include "cmdline_component.h"
#include "std_wrappers.h"

struct command_component * command_component_create_command(Command cmd)
{
    struct command_component * cmp = xmalloc(sizeof *cmp);
    cmp->type = CT_COMMAND;
    cmp->content.cmd = cmd;
    return cmp;
}

struct command_component *
command_component_create_operator(const enum shell_operator_type operator)
{
    struct command_component * cmp = xmalloc(sizeof *cmp);
    cmp->type = CT_OPERATOR;
    cmp->content.operator = operator;
    return cmp;
}

void command_component_destroy(struct command_component * cmp)
{
    if ( cmp->type == CT_COMMAND ) {
        command_destroy(cmp->content.cmd);
    }
    free(cmp);
}

void command_component_print(struct command_component * cmp)
{
    if ( cmp->type == CT_COMMAND ) {
        command_print(cmp->content.cmd);
    }
    else {
        operator_print(cmp->content.operator);
    }
}
