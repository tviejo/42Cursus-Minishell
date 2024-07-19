# include "../includes/minishell.h"

int cmd_process(char **cmd, t_command_tree *tree, t_exec *exec, int index)
{
    exec->pid[index] = fork();
    if (exec->pid[index] == -1)
    {
        ft_putstr_fd("fork failed\n", 2);
        return (EXIT_FAILURE);
    }
    else if (exec->pid[index] == 0)
    {
        exec_cmd(tree, exec, cmd);
    }
    else
    {
        waitpid(exec->pid[index], &status, 0);
    }
}