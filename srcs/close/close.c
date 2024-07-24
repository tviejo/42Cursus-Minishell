#include "../includes/minishell.h"

int	ft_close_error(t_command_tree *tree, t_data *exec)
{
	(void)*tree;
	(void)*exec;
	return (EXIT_FAILURE);
}