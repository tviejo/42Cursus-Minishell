#include "../includes/minishell.h"

int	find_builtin(t_command_tree *tree)
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

int	exec_builtin(t_command_tree *tree, t_exec *exec)
{
	int	builtin;

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

int	main(int argc, char **argv, char **env)
{
	t_exec			exec;
	t_command_tree	tree;

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
