# include "../includes/minishell.h"

bool is_and_or(t_command_tree *tree)
{
    if (tree->type == nt_AND || tree->type == nt_OR)
        return (true);
    return (false);
}