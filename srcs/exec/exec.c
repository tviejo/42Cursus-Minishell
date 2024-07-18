# include "../includes/minishell.h"

int    exec(t_command_tree *tree)
{
    int i;

    i = 0;
    if (tree->type == AND)
    {
        if (exec(tree->left) == 1)
            return (exec(tree->right));
        else
            return (0);
    }
    else if (tree->type == OR)
    {
        if (exec(tree->left) == 0)
            return (exec(tree->right));
    }
    else if (tree->type == pipe)
    {
        return (exec(tree->left), exec(tree->right));
    }
    else if (tree->type == command)
    {
        return (exec_command(tree));
    }
}
