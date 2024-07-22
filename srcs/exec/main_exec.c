#include "../includes/minishell.h"

int	exec_command(t_command_tree *tree, t_exec *exec)
{
	cmd_process_and_or(tree, exec);
	return (EXIT_SUCCESS);
}

int	exec_pipe(t_command_tree *tree, t_exec *exec)
{
	child_process(tree, exec);
	return (EXIT_SUCCESS);
}
int	exec_cmdtree(t_command_tree *tree, t_exec *exec)
{
	if (tree == NULL)
		return (EXIT_SUCCESS);
	if (tree->type == nt_command)
	{
		if (exec->oldtype == nt_pipe && exec->side == e_left)
			exec_pipe(tree, exec);
		// else if (exec->nexttype == nt_pipe)
		// 	exec_pipe(tree, exec);
		else if (exec->oldtype == nt_pipe && exec->side == e_right)
		{
			last_child_process(tree, exec);
			wait_all_process();
		}
		else if (exec->side == e_left && (exec->oldtype == nt_OR || exec->oldtype == nt_AND))
			exec_command(tree, exec);
		else if (exec->side == e_right && (exec->oldtype == nt_OR || exec->oldtype == nt_AND))
		{
			if (g_signal == 0 && exec->oldtype == nt_AND)
				exec_command(tree, exec);
			else if (g_signal != 0 && exec->oldtype == nt_OR)
				exec_command(tree, exec);
		}
		else
		{
			write(2, "exec_command\n", 13);
			exec_command(tree, exec);
		}
	}
	if (tree->type != nt_command && tree->left != NULL)
	{
		exec->nexttype = exec->oldtype;
		exec->oldtype = tree->type;
		exec->side = e_left;
		exec_cmdtree(tree->left, exec);
	}
	if (tree->type != nt_command && tree->right != NULL)
	{
		exec->nexttype = exec->oldtype; 
		exec->oldtype = tree->type;
		exec->side = e_right;
		exec_cmdtree(tree->right, exec);
	}
	return (EXIT_SUCCESS);
}
/*
int	main(int argc, char **argv, char **env)
{
	t_exec			exec;
	t_command_tree	tree;

	signal(SIGINT, signal_handler);
	argc = 0;
	argv = NULL;
	store_env(&exec, env);
	tree.nb_command = 3;
	calloc_pid(&exec, &tree);
	// tree.type = nt_here_doc;
	// tree.argument = malloc(sizeof(char *) * 4);
	// tree.argument[0] = "LIMITER";
	// tree.argument[1] = NULL;
	// tree.argument[2] = NULL;
	// tree.argument[3] = NULL;
	// here_doc(&tree, &exec);
	// free(tree.argument);
	tree.type = nt_pipe;
	tree.argument = malloc(sizeof(char *) * 4);
	tree.argument[0] = "ls";
	tree.argument[1] = "-l";
	tree.argument[2] = NULL;
	tree.argument[3] = NULL;
	exec_pipe(&tree, &exec);
	// cmd_process_and_or(&tree, &exec);
	// if (wait_one_process() == true)
	// {
		// free(tree.argument);
		// tree.type = nt_pipe;
		// tree.argument = malloc(sizeof(char *) * 4);
		// tree.argument[0] = "outfile";
		// tree.argument[1] = NULL;
		// tree.argument[2] = NULL;
		// tree.argument[3] = NULL;
		// redir_outfile(&tree, &exec);
		free(tree.argument);
		tree.argument = malloc(sizeof(char *) * 4);
		tree.argument[0] = "wcfd";
		tree.argument[1] = "-c";
		tree.argument[2] = NULL;
		tree.argument[3] = NULL;
		last_child_process(&tree, &exec);
		wait_all_process();
	// }
	free_env(&exec);
	ft_free_pid(&exec);
	free(tree.argument);
	return (g_signal);
}
*/