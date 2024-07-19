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

void	ft_free_cmd(char	**cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
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
	ft_printf("command not found: %s\n", cmd[0]);
	ft_free_cmd(cmd);
	return (free(tmppath), free(tmp), NULL);
}
