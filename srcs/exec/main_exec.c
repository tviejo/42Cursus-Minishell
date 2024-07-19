# include "../includes/minishell.h"

int exec_command(t_command_tree *tree, t_exec *exec)
{
    cmd_process(tree->argument, tree, exec, 0);
    return (EXIT_SUCCESS);
}
/*
int	main(int argc, char **argv, char **env)
{
	t_exec			exec;
	t_command_tree	tree;

	argc = 0;
	argv = NULL;
	store_env(&exec, env);
    tree.nb_command = 1;
	tree.type = nt_command;
	tree.argument = malloc(sizeof(char *) * 4);
	tree.argument[0] = "ls";
	tree.argument[1] = "-l";
	tree.argument[2] = NULL;
	tree.argument[3] = NULL;
    calloc_pid(&exec, &tree);
	exec_command(&tree, &exec);
	free_env(&exec);
    ft_free_pid(&exec);
	free(tree.argument);
	return (EXIT_SUCCESS);
}
*/