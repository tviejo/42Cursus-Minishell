# include "../includes/minishell.h"

int ft_pwd(t_data *exec)
{
    char	pwd[4096];
	char	*pwd2;

	pwd2 = ft_strjoin("PWD=", getcwd(pwd, 4096));
	update_pwd(exec, pwd2);
    ft_putstr_fd(pwd2, 1);
    free(pwd2);
    ft_putstr_fd("\n", 1);
    return (EXIT_SUCCESS);
}