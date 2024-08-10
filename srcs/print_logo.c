/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:47:13 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/10 09:51:31 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_dprintf(2, CMAGENTA CBOLD);
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
