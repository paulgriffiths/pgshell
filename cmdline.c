#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cmdline.h"
#include "std_wrappers.h"
#include "shell_token.h"

#define INITIAL_LIST_SIZE 8

struct command_component_list {
    struct command_component ** components;
    size_t length;
    size_t capacity;
};

CmdCmpList cmdline_create(TokenList list)
{
    struct command_component_list * new_list = xmalloc(sizeof *new_list);
    new_list->capacity = INITIAL_LIST_SIZE;
    new_list->length = 0;
    new_list->components = xmalloc(new_list->capacity *
                                   sizeof *new_list->components);
    Command cmd = NULL;

    for ( size_t i = 0; i < token_list_length(list); ++i ) {
        struct shell_token * token = token_list_token_at_index(list, i);
        if ( token->type == STT_STRING ) {
            if ( !cmd ) {
               cmd = command_create();
            } 
            command_add_argument(cmd, token->content.str);
        }
        else {
            if ( cmd ) {
                cmdline_add_command(new_list, cmd);
                cmd = NULL;
            }
        }

        if ( token->type == STT_OPERATOR ) {
            cmdline_add_operator(new_list, token->content.operator);
        }
    }


    if ( cmd ) {
        cmdline_add_command(new_list, cmd);
        cmd = NULL;
    }

    return new_list;
}

void cmdline_destroy(CmdCmpList list)
{
    for ( size_t i = 0; i < list->length; ++i ) {
        struct command_component * cmp = list->components[i];
        if ( cmp->type == CT_COMMAND ) {
            command_destroy(cmp->content.cmd);
        }
        free(cmp);
    }
    free(list->components);
    free(list);
}

size_t cmdline_length(CmdCmpList list)
{
    return list->length;
}

void cmdline_expand_if_needed(CmdCmpList list)
{
    if ( list->length + 1 >= list->capacity ) {
        list->capacity *= 2;
        list->components = realloc(list->components, 
                list->capacity * sizeof *list->components);
    }
}

void cmdline_add_command(CmdCmpList list, Command cmd)
{
    struct command_component * new_comp = xmalloc(sizeof *new_comp);
    new_comp->type = CT_COMMAND;
    new_comp->content.cmd = cmd;
    cmdline_expand_if_needed(list);
    list->components[list->length++] = new_comp;
}

void cmdline_add_operator(CmdCmpList list, enum shell_operator_type operator)
{
    struct command_component * new_comp = xmalloc(sizeof *new_comp);
    new_comp->type = CT_OPERATOR;
    new_comp->content.operator = operator;
    cmdline_expand_if_needed(list);
    list->components[list->length++] = new_comp;
}

struct command_component * cmdline_component_at_index(CmdCmpList list,
        const size_t index)
{
    return list->components[index];
}

void cmdline_print(CmdCmpList list)
{
    for ( size_t i = 0; i < list->length; ++i ) {
        struct command_component * cmp = list->components[i];
        command_component_print(cmp);
    }
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

bool cmdline_is_valid(CmdCmpList list)
{
    if ( list->length > 0 && list->components[0]->type == CT_COMMAND ) {
        return true;
    }
    else {
        return false;
    }
}

