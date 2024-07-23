# include "../includes/minishell.h"

int cmd_process_and_or(t_command_tree *tree, t_exec *exec)
{
    int status;
    int index;
    
    signal(SIGINT, signal_handler_process);
    if (find_builtin(tree) > 0)
    {
        exec_builtin(tree, exec);
        return (EXIT_SUCCESS);
    }
    index = create_fork(tree, exec);
    if (exec->pid[index] == 0)
    {
        exec_cmd(tree, exec);
    }
    else
    {
        waitpid(exec->pid[index], &status, 0);
        g_signal = WEXITSTATUS(status);
    }
    return (EXIT_SUCCESS);
}