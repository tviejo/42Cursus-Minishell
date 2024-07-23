# include "../includes/minishell.h"

int ft_pwd(t_exec *exec)
{
    char	pwd[4096];
	char	*pwd2;

	pwd2 = ft_strjoin("PATH=", getcwd(pwd, 4096));
	update_pwd(exec, pwd2);
    ft_putstr_fd(pwd2, 1);
    free(pwd2);
    ft_putstr_fd("\n", 1);
    return (EXIT_SUCCESS);
}