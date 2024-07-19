# include "../includes/minishell.h"

int ft_pwd(t_exec *exec)
{
    ft_putstr_fd(find_path("PWD=", exec), 1);
    ft_putstr_fd("\n", 1);
    return (EXIT_SUCCESS);
}