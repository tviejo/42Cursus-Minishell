/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:40 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/10 12:09:28 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (NULL);
}

static char	*find_good_path(char **cmd, char **paths)
{
	char	*tmp;
	char	*tmppath;
	int		i;

	i = -1;
	tmp = NULL;
	tmppath = NULL;
	if (cmd == NULL || cmd[0] == NULL || cmd[0][0] == '\0')
		return (NULL);
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
	return (free(tmppath), free(tmp), cmd[0]);
}

char	*find_cmd(char **cmd, char **paths)
{
	char	*tmp;

	tmp = NULL;
	if (access(cmd[0], F_OK) == 0)
	{
		if (paths != NULL)
			ft_free_split(paths);
		if (access(cmd[0], F_OK | X_OK) == 0)
			return (cmd[0]);
		else
		{
			return (cmd[0]);
		}
	}
	if (cmd != NULL && paths != NULL)
	{
		tmp = find_good_path(cmd, paths);
	}
	ft_free_split(paths);
	return (tmp);
}
