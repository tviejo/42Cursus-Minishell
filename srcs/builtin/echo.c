# include "../includes/minishell.h"

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