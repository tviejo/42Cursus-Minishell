#include "../includes/minishell.h"

void	ft_is_cmd(t_command_tree *tree, t_data *exec)
{
	ft_putstr_fd("cmd", 2);
	if (exec->oldtype == nt_pipe)
	{
		last_child_process(tree, exec);
		wait_all_process(exec);
	}
	else if (exec->side == e_left && (exec->oldtype == nt_OR
			|| exec->oldtype == nt_AND))
		cmd_process_and_or(tree, exec);
	else if (exec->side == e_right && (exec->oldtype == nt_OR
			|| exec->oldtype == nt_AND))
	{
		if (exec->error_code == 0 && exec->oldtype == nt_AND)
			cmd_process_and_or(tree, exec);
		else if (exec->error_code != 0 && exec->oldtype == nt_OR)
		{
			exec->error_code = 0;
			cmd_process_and_or(tree, exec);
		}
	}
	else
		cmd_process_and_or(tree, exec);
	dup2(exec->dupstdin, STDIN_FILENO);
	dup2(exec->dupstdout, STDOUT_FILENO);
	tree->type = nt_exec_done;
}
void	ft_redir(t_command_tree *tree, t_data *exec)
{
	if (tree->type == nt_out_truncate || tree->type == nt_out_append)
	{
		tree->type = nt_exec_done;
		redir_outfile(tree, exec);
	}
	if (tree->type == nt_infile)
	{
		tree->type = nt_exec_done;
		redir_infile(tree, exec);
	}
}

bool	is_node(t_command_tree *tree)
{
	if (tree->type == nt_piped_cmd)
		return (false);
	else if (tree->type == nt_command)
		return (false);
	else
		return (true);
}

bool	is_redir(t_command_tree *tree)
{
	if (tree->type == nt_out_truncate)
		return (true);
	else if (tree->type == nt_out_append)
		return (true);
	else if (tree->type == nt_infile)
		return (true);
	else
		return (false);
}
int	exec_cmdtree(t_command_tree *tree, t_data *exec)
{
	if (tree == NULL || tree->type == nt_exec_done)
		return (EXIT_SUCCESS);
	else if (tree->type == nt_piped_cmd)
		child_process(tree, exec);
	else if (tree->type == nt_command)
		ft_is_cmd(tree, exec);
	if (is_node(tree) == true && tree->left != NULL)
	{
		if (is_redir(tree) == true)
			ft_redir(tree, exec);
		exec->oldtype = tree->type;
		exec->side = e_left;
		exec_cmdtree(tree->left, exec);
	}
	if (is_node(tree) == true && tree->right != NULL)
	{
		if (is_redir(tree) == true)
			ft_redir(tree, exec);
		exec->oldtype = tree->type;
		exec->side = e_right;
		exec_cmdtree(tree->right, exec);
	}
	return (EXIT_SUCCESS);
}