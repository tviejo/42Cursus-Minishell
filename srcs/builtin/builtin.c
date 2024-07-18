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

int find_builtin(t_command_tree *tree)
{
    if (!ft_strncmp(tree->argument[0], "echo", 5))
        return (b_echo);
    else if (!ft_strncmp(tree->argument[0], "cd", 3))
        return (b_cd);
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
    return (EXIT_FAILURE);
}

int main(int argc, char **argv, char **env)
{
    t_exec exec;
    t_command_tree tree;

    argc = 0;
    argv = NULL;
    store_env(&exec, env);
    tree.type = command;
    tree.argument = malloc(sizeof(char *) * 4);
    tree.argument[0] = malloc(sizeof(char) * 4);
    tree.argument[0] = "echo";
    tree.argument[1] = malloc(sizeof(char) * 6);
    tree.argument[1] = "-n";
    tree.argument[2] = malloc(sizeof(char) * 6);
    tree.argument[2] = "srcs/";
    tree.argument[3] = malloc(sizeof(char) * 6);
    tree.argument[3] = NULL;
    exec_builtin(&tree, &exec);
    return (EXIT_SUCCESS);
}
