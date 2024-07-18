/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:19:40 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/17 23:55:56 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*cmdline;

	rl_bind_key('\t', rl_complete);
	using_history();
	while (1)
	{
		cmdline = readline("minishell> ");
		if (!cmdline)
			break ;
		add_history(cmdline);

		free(cmdline);
	}
	return (0);
}
