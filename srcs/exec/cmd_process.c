# include "../includes/minishell.h"

int cmd_process(char **cmd, t_command_tree *tree, t_exec *exec)
{
    int status;
    int index;
    
    index = create_fork(tree, exec);
    if (exec->pid[index] == 0)
    {
        exec_cmd(tree, exec, cmd);
    }
    else
    {
        waitpid(exec->pid[index], &status, 0);
    }
    return (EXIT_SUCCESS);
}