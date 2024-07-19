# include "../includes/minishell.h"

int redir_outfile_append(char **argument, t_command_tree *tree, t_exec *exec)
{
    int fd;

    if (tree->type = nt_out_append)
        fd = open(argument, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(argument, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        ft_putstr_fd("open failed\n", 2);
        return (EXIT_FAILURE);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (EXIT_SUCCESS);
}