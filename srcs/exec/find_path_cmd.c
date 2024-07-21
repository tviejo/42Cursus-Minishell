# include "../includes/minishell.h"

char	*find_path_cmd(char **envp)
{
	while (ft_strncmp(*envp, "PATH=", 5) != 0 && *envp != NULL)
		envp++;
	if (ft_strncmp(*envp, "PATH=", 5) == 0)
		return (*envp + 5);
	else
	{
		return (NULL);
	}
}

char	*find_cmd(char **cmd, char **paths)
{
	char	*tmp;
	char	*tmppath;
	int		i;

	i = 0;
	tmp = NULL;
	tmppath = NULL;
	while (paths[i] != NULL)
	{
		free(tmp);
		free(tmppath);
		tmppath = ft_strjoin(paths[i], "/");
		if (tmppath == NULL)
			break ;
		tmp = ft_strjoin(tmppath, cmd[0]);
		if (tmp != NULL && access(tmp, F_OK | X_OK) == 0)
		{
			free(tmppath);
			return (tmp);
		}
		i++;
	}
	ft_printf("minishell: %s: command not found\n", cmd[0]);
	g_signal = 127;
	return (free(tmppath), free(tmp), NULL);
}
