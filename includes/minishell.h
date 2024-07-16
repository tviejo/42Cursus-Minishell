#ifndef MINISHEL_H
# define MINISHELL_H

# include "mini_tviejo.h"
# include "mini_ade_sarr.h"

enum e_type
{
    command,
    infile,
    outfile_create,
    outfile_append,
    pipe,
    OR,
    AND,
};

typedef struct command_tree
{
    enum e_type type;
    char **argument;
    struct command_tree *left;
    struct command_tree *right;
} t_command_tree;

#endif