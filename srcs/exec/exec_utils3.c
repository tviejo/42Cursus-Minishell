# include "../includes/minishell.h"

void    init_exec(t_data *mshell)
{
    mshell->end_exec = false;
    mshell->error_code = 0;
    mshell->oldtype = 0;
    mshell->side = e_left;
    calloc_pid(mshell, mshell->cmdtree);
    mshell->dupstdin = dup(STDIN_FILENO);
    mshell->dupstdout = dup(STDOUT_FILENO);
}

void    close_exec(t_data *mshell)
{
    dup2(mshell->dupstdin, STDIN_FILENO);
	dup2(mshell->dupstdout, STDOUT_FILENO);
	close(mshell->dupstdout);
	close(mshell->dupstdin);
	ft_free_pid(mshell);
}