/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 04:05:33 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/09 20:49:00 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_back_env(t_data *exec, char *env_var)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (exec->env_len + 2));
	while (exec->env[i])
	{
		new_env[i] = ft_strdup(exec->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(env_var);
	new_env[i + 1] = NULL;
	exec->env_len++;
	free_env(exec);
	return (new_env);
}

char	*get_env_var(t_data *ms, char *varname)
{
	const int	namelen = ft_strlen(varname);
	int			i;

	i = -1;
	while (ms->env[++i])
		if (ft_strncmp(ms->env[i], varname, namelen) == 0
			&& ms->env[i][namelen] == '=')
			return (ms->env[i] + namelen + 1);
	return (NULL);
}
