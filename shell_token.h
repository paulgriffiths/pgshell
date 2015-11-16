#ifndef PG_SHELL_SHELL_TOKEN_H
#define PG_SHELL_SHELL_TOKEN_H

enum shell_token_type {
    STT_STRING,
    STT_OPERATOR
};

enum shell_operator_type {
    SOT_PIPE,
    SOT_REDIRECT_LEFT,
    SOT_REDIRECT_RIGHT
};

struct shell_token {
    enum shell_token_type type;
    union {
        char * str;
        enum shell_operator_type operator;
    } content;
};

struct shell_token * string_token_create(const char * str);
struct shell_token * operator_token_create(const enum shell_operator_type type);
void shell_token_destroy(struct shell_token * token);
void operator_print(const enum shell_operator_type type);
void shell_token_print(struct shell_token * token);

#endif      /*  PG_SHELL_SHELL_TOKEN_H  */
