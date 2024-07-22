# include "../includes/minishell.h"

int create_fork(t_command_tree *tree, t_exec *exec)
{
    int index;

    index = 0;
    while (exec->pid[index] != -10)
        index++;
    exec->pid[index] = fork();
    if (exec->pid[index] == -1)
        ft_close_error(tree, exec);
    return (index);
}