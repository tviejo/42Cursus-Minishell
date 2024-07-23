#include "../includes/minishell.h"

char	*find_path_cmd(char **envp)
{
	if (envp == NULL)
		return (NULL);
	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (*envp == NULL)
		return (NULL);
	if (ft_strncmp(*envp, "PATH=", 5) == 0)
		return (*envp + 5);
	else
	{
		return (NULL);
	}
}
static char	*find_good_path(char **cmd, char **paths)
{
	char	*tmp;
	char	*tmppath;
	int		i;

	i = -1;
	tmp = NULL;
	tmppath = NULL;
	while (paths[++i] != NULL)
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
	}
	return (free(tmppath), free(tmp), NULL);
}

char	*find_cmd(char **cmd, char **paths)
{
	char *tmp;

	tmp = NULL;
	if (access(cmd[0], F_OK | X_OK) == 0)
		return (ft_strdup(cmd[0]));
	if (cmd != NULL && paths != NULL)
	{
		tmp = find_good_path(cmd, paths);
	}
	if (tmp != NULL)
		return (tmp);
	else
		return (NULL);
}
