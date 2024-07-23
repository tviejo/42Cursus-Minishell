#include "../includes/minishell.h"

bool	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0 && !((str[i] == '-' || str[i] == '+')
				&& i == 0))
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(t_command_tree *tree)
{
	if (tree->argument[1] != NULL)
	{
		if (tree->argument[2] != NULL)
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			return (EXIT_FAILURE);
		}
		else if (ft_isnumber(tree->argument[1]) == false)
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(tree->argument[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (EXIT_FAILURE);
		}
		else
		{
			if (ft_atoi(tree->argument[1]) > 255 || atoi(tree->argument[1]) < 255)
				exit(255);
			exit(ft_atoi(tree->argument[1]));
		}
	}
	exit(0);
    return (EXIT_SUCCESS);
}