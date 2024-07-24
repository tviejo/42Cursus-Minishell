# include "../includes/minishell.h"

static bool check_option(char *arg)
{
	int		j;
	bool	backslash;

	backslash = true;
	if (arg != NULL && ft_strncmp(arg, "-", 1) == 0)
	{
		j = 1;
		while (arg[j] == 'n')
			j++;
		if (arg[j] == '\0')
			backslash = false;
	}
	return (backslash);
}

int	ft_echo(t_command_tree *tree)
{
	int		i;
	bool	backslash;

    backslash = check_option(tree->argument[1]);
	if (backslash == true)
		i = 1;
	else
		i = 2;
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
