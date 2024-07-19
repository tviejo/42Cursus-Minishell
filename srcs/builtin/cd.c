# include "../includes/minishell.h"

int ft_cd(t_command_tree *tree, t_exec *exec)
{
    char *pwd;

    if (tree->argument[1] == NULL)
    {
        update_oldpwm(exec);
        update_pwd(exec, find_path("HOME=", exec));
        chdir(find_path("HOME=", exec));
        return (EXIT_SUCCESS);
    }
    else if (chdir(tree->argument[1]) == -1)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(tree->argument[1], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (EXIT_FAILURE);
    }
    update_oldpwm(exec);
    pwd = ft_strjoin(find_path("PWD=", exec), "/");
    pwd = ft_strjoin(pwd, tree->argument[1]);
    opendir(pwd);
    update_pwd(exec, pwd);
    return (EXIT_SUCCESS);
}