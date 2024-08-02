/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:11:44 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/02 13:51:12 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	init_sub_mshell(t_data *sub_mshell, t_data *mshell)
{
	sub_mshell->error_code = 0;
	sub_mshell->env_len = mshell->env_len;
	sub_mshell->debug_mode = 0;
	if (!init_parsing(sub_mshell))
	{
		ft_putstr_fd("minishell [init_parsing]: error: malloc failed.\n", 2);
		exit(2);
	}
	sub_mshell->env = ft_strdup_env(mshell->env);
	return (EXIT_SUCCESS);
}

int	exec_subshell(char *cmdline, t_data *mshell)
{
	t_data	sub_mshell;

	init_sub_mshell(&sub_mshell, mshell);
	lex_and_parse(&sub_mshell, cmdline);
	execute(&sub_mshell);
	free_cmdtree(&sub_mshell);
	free_parsing(&sub_mshell);
	free_env(&sub_mshell);
	return (sub_mshell.error_code);
}
