/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:37:05 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/06 19:06:17 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	bad_token(char *cmdline, t_data *ms)
{
	if (*cmdline == '\\' || *cmdline == '!' || *cmdline == ':'
		|| *cmdline == ';')
	{
		ft_dprintf(2, "minishell: bad token '%c'\n", *cmdline);
		purger_lexqueue(ms->file_lex);
		ms->error_code = 2;
		return (true);
	}
	return (false);
}
