# include "../includes/minishell.h"

int exec_command(t_command_tree *tree, t_exec *exec)
{
    cmd_process(tree->argument, tree, exec, 0);
    return (EXIT_SUCCESS);
}

int exec_pipe(t_command_tree *tree, t_exec *exec)
{
    static int index = 0;
    child_process(tree->argument, tree, exec, index);
    index++;
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
    tree.nb_command = 2;
	tree.type = nt_pipe;
	tree.argument = malloc(sizeof(char *) * 4);
	tree.argument[0] = "ls";
	tree.argument[1] = "-l";
	tree.argument[2] = NULL;
	tree.argument[3] = NULL;
    calloc_pid(&exec, &tree);
	exec_pipe(&tree, &exec);
    free(tree.argument);
    tree.argument = malloc(sizeof(char *) * 4);
	tree.argument[0] = "wc";
	tree.argument[1] = "-c";
	tree.argument[2] = NULL;
	tree.argument[3] = NULL;
    last_child_process(tree.argument, &tree, &exec, 1);
    while (waitpid(-1, NULL, 0) > 0)
		;
	free_env(&exec);
    ft_free_pid(&exec);
	free(tree.argument);
	return (EXIT_SUCCESS);
}
*/