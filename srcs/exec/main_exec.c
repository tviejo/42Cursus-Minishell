# include "../includes/minishell.h"

int exec_command(t_command_tree *tree, t_exec *exec)
{
    cmd_process(tree->argument, tree, exec);
    return (EXIT_SUCCESS);
}

int exec_pipe(t_command_tree *tree, t_exec *exec)
{
    child_process(tree->argument, tree, exec);
    return (EXIT_SUCCESS);
}


int	main(int argc, char **argv, char **env)
{
	t_exec			exec;
	t_command_tree	tree;

	argc = 0;
	argv = NULL;
	store_env(&exec, env);
    tree.nb_command = 3;
	tree.type = nt_here_doc;
	tree.argument = malloc(sizeof(char *) * 4);
	tree.argument[0] = "LIMITER";
	tree.argument[1] = NULL;
	tree.argument[2] = NULL;
	tree.argument[3] = NULL;
	calloc_pid(&exec, &tree);
	handle_here_doc(&tree, &exec);
	free(tree.argument);
	tree.type = nt_pipe;
	tree.argument = malloc(sizeof(char *) * 4);
	tree.argument[0] = "cat";
	tree.argument[1] = NULL;
	tree.argument[2] = NULL;
	tree.argument[3] = NULL;
	exec_pipe(&tree, &exec);
    free(tree.argument);
	tree.type = nt_pipe;
	tree.argument = malloc(sizeof(char *) * 4);
	tree.argument[0] = "cat";
	tree.argument[1] = NULL;
	tree.argument[2] = NULL;
	tree.argument[3] = NULL;
	redir_outfile(&tree, &exec);
    free(tree.argument);
    tree.argument = malloc(sizeof(char *) * 4);
	tree.argument[0] = "wc";
	tree.argument[1] = "-c";
	tree.argument[2] = NULL;
	tree.argument[3] = NULL;
    last_child_process(tree.argument, &tree, &exec);
    while (waitpid(-1, NULL, 0) > 0)
		;
	free_env(&exec);
    ft_free_pid(&exec);
	free(tree.argument);
	return (EXIT_SUCCESS);
}