/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:47:13 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/12 10:13:13 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shell_level(t_data *mshell)
{
	int		i;
	char	*level;
	char	*tmp;
	char	buffer[4096];

	i = -1;
	while (mshell->env[++i])
	{
		if (ft_strncmp(mshell->env[i], "SHLVL=", 6) == 0)
		{
			level = ft_substr(mshell->env[i], 6, ft_strlen(mshell->env[i]) - 6);
			tmp = ft_itoa(ft_atoi(level) + 1);
			free(level);
			free(mshell->env[i]);
			mshell->env[i] = ft_strjoin("SHLVL=", tmp);
			free(tmp);
		}
		else if (ft_strncmp(mshell->env[i], "SHELL=", 6) == 0)
		{
			free(mshell->env[i]);
			mshell->env[i] = ft_strjoin("SHELL=", getcwd(buffer, 4096));
		}
	}
}

static bool	search_term_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "TERM=xterm-256color", 19) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	clear_terminal(char **env)
{
	char	*arg[2];

	arg[0] = "/usr/bin/clear";
	arg[1] = NULL;
	if (CLEAR_MODE && search_term_env(env) == true)
	{
		if (fork() == 0)
		{
			execve(arg[0], arg, env);
			exit(0);
		}
		wait(NULL);
	}
}

int	print_minishell(void)
{
	ft_dprintf(2, "\n" CMAGENTA CBOLD);
	ft_dprintf(2, L1 "\n");
	ft_dprintf(2, L2 "\n");
	ft_dprintf(2, L3 "\n");
	ft_dprintf(2, L4 "\n");
	ft_dprintf(2, L5 "\n");
	ft_dprintf(2, L6 "\n\n");
	ft_dprintf(2, "Thomas Viejo & Aurélien de Sarrau (juillet-aout 2024)\n\n");
	ft_dprintf(2, RESET);
	return (0);
}

char	*create_prompt(t_data *mshell)
{
	char	*prompt;
	char	*prompt2;
	char	buffer[4096];

	getcwd(buffer, 4096);
	prompt2 = ft_strjoin(CBLUE CBOLD, buffer);
	prompt = ft_strjoin(prompt2, RESET);
	free(prompt2);
	if (mshell->error_code != 0)
		prompt2 = ft_strjoin(prompt, CRED CBOLD);
	else
		prompt2 = ft_strjoin(prompt, CGREEN CBOLD);
	free(prompt);
	prompt = ft_strjoin(prompt2, " minishell> ");
	free(prompt2);
	prompt2 = ft_strjoin(prompt, RESET);
	free(prompt);
	return (prompt2);
}
