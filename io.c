#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "io.h"

static void output_prompt(void);

bool get_input_line(char * buffer, const size_t size)
{
    do {
        output_prompt();

        if ( !fgets(buffer, size, stdin) ) {
            return false;
        }

        const size_t len = strlen(buffer);
        if ( len > 0 && buffer[len - 1] == '\n' ) {
            buffer[len - 1] = '\0';
        }
    } while ( buffer[0] == '\0' );

    return true;
}

static void output_prompt(void)
{
    printf("shell$ ");
    fflush(stdout);
}
