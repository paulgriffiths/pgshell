#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cmdline.h"
#include "cmdline_component.h"
#include "std_wrappers.h"
#include "shell_token.h"
#include "shell_token_list.h"

#define INITIAL_LIST_SIZE 8

static void cmdline_expand_if_needed(CmdCmpList list);

struct command_component_list {
    struct command_component ** cmps;
    size_t length;
    size_t capacity;
};

CmdCmpList cmdline_create(TokenList list)
{
    struct command_component_list * new_list = xmalloc(sizeof *new_list);
    new_list->capacity = INITIAL_LIST_SIZE;
    new_list->length = 0;
    new_list->cmps = xmalloc(new_list->capacity * sizeof *new_list->cmps);
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
        command_component_destroy(list->cmps[i]);
    }
    free(list->cmps);
    free(list);
}

size_t cmdline_length(CmdCmpList list)
{
    return list->length;
}

void cmdline_add_command(CmdCmpList list, Command cmd)
{
    cmdline_expand_if_needed(list);
    list->cmps[list->length++] = command_component_create_command(cmd);
}

void cmdline_add_operator(CmdCmpList list, enum shell_operator_type operator)
{
    cmdline_expand_if_needed(list);
    list->cmps[list->length++] = command_component_create_operator(operator);
}

struct command_component * cmdline_component_at_index(CmdCmpList list,
        const size_t index)
{
    return list->cmps[index];
}

void cmdline_print(CmdCmpList list)
{
    for ( size_t i = 0; i < list->length; ++i ) {
        command_component_print(list->cmps[i]);
    }
}

bool cmdline_is_valid(CmdCmpList list)
{
    if ( list->length > 0 && list->cmps[0]->type == CT_COMMAND ) {
        return true;
    }
    else {
        return false;
    }
}

static void cmdline_expand_if_needed(CmdCmpList list)
{
    if ( list->length + 1 >= list->capacity ) {
        list->capacity *= 2;
        list->cmps = realloc(list->cmps, list->capacity * sizeof *list->cmps);
    }
}

