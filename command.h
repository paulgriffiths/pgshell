#ifndef PG_SHELL_COMMAND_H
#define PG_SHELL_COMMAND_H

#include <stddef.h>

typedef struct shell_command * Command;

Command command_create(void);
void command_destroy(Command cmd);
void command_add_argument(Command cmd, const char * arg);
size_t command_num_args(Command cmd);
char ** command_raw_args(Command cmd);
char * command_command(Command cmd);
void command_print(Command cmd);

#endif      /*  PG_SHELL_COMMAND_H  */
