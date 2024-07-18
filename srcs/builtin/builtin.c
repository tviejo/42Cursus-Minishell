#include "../includes/minishell.h"

int	ft_echo(t_command_tree *tree)
{
	int		i;
	bool	backslash;

	i = 1;
    backslash = false;
	if (tree->argument[1] && !ft_strncmp(tree->argument[1], "-n", 2))
	{
		backslash = true;
		i++;
	}
	while (tree->argument[i])
	{
		if (i != 1)
			write(1, " ", 1);
		write(1, tree->argument[i], ft_strlen(tree->argument[i]));
		i++;
	}
    if (backslash == true)
	    write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

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

int ft_env(t_exec *exec)
{
    int i;

    i = 0;
    while (exec->env[i])
    {
        ft_putstr_fd(exec->env[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    return (EXIT_SUCCESS);
}

int ft_pwd(t_exec *exec)
{
    ft_putstr_fd(find_path("PWD=", exec), 1);
    ft_putstr_fd("\n", 1);
    return (EXIT_SUCCESS);
}
int ft_unset(t_command_tree *tree, t_exec *exec)
{
    int i;

    i = 0;
    while (exec->env[i])
    {
        if (ft_strncmp(exec->env[i], tree->argument[1], ft_strlen(tree->argument[1])))
        {
            while (exec->env[i + 1] != NULL)
            {
                free(exec->env[i]);
                exec->env[i] = ft_strdup(exec->env[i + 1]);
                i++;
            }
            free(exec->env[i]);
            exec->env[i] = NULL;
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

int ft_export(t_command_tree *tree, t_exec *exec)
{
    int i;
    char **new_env;

    i = 0;
    while (exec->env[i])
    {
        if (ft_strncmp(exec->env[i], tree->argument[1], ft_strlen(tree->argument[1])))
        {
            free(exec->env[i]);
            exec->env[i] = ft_strdup(tree->argument[1]);
            return (EXIT_SUCCESS);
        }
        i++;
    }
    exec->env = expand_env(exec);
    return (EXIT_SUCCESS);
}

int find_builtin(t_command_tree *tree)
{
    if (!ft_strncmp(tree->argument[0], "echo", 5))
        return (b_echo);
    else if (!ft_strncmp(tree->argument[0], "cd", 3))
        return (b_cd);
    else if (!ft_strncmp(tree->argument[0], "env", 4))
        return (b_env);
    else if (!ft_strncmp(tree->argument[0], "pwd", 4))
        return (b_pwd);
    else if (!ft_strncmp(tree->argument[0], "unset", 6))
        return (b_unset);
    else if (!ft_strncmp(tree->argument[0], "export", 7))
        return (b_export);
    else if (!ft_strncmp(tree->argument[0], "exit", 5))
        return (b_exit);
    return (EXIT_FAILURE);
}

int exec_builtin(t_command_tree *tree, t_exec *exec)
{
    int builtin;

    builtin = find_builtin(tree);
    if (builtin == b_echo)
        return (ft_echo(tree));
    else if (builtin == b_cd)
        return (ft_cd(tree, exec));
    else if (builtin == b_env)
        return (ft_env(exec));
    else if (builtin == b_pwd)
        return (ft_pwd(exec));
    else if (builtin == b_unset)
        return (ft_unset(tree, exec));
    else if (builtin == b_export)
        return (ft_export(tree, exec));
    else if (builtin == b_exit)
        exit(EXIT_SUCCESS);
    return (EXIT_FAILURE);
}

int main(int argc, char **argv, char **env)
{
    t_exec exec;
    t_command_tree tree;

    argc = 0;
    argv = NULL;
    store_env(&exec, env);
    tree.type = nt_command;
    tree.argument = malloc(sizeof(char *) * 4);
    tree.argument[0] = "export";
    tree.argument[1] = "NEW_VAR=42";
    tree.argument[2] = "srcs/"; 
    tree.argument[3] = NULL;
    exec_builtin(&tree, &exec);
    ft_env(&exec);
    free_env(&exec);
    free(tree.argument[3]);
    free(tree.argument);
    return (EXIT_SUCCESS);
}
