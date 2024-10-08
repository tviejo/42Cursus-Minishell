/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:37:05 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/12 18:44:25 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	unsupported_token(t_data *ms, char *cmdline)
{
	if ((*cmdline == '&' && cmdline[1] != '&')
		|| *cmdline == '!' || *cmdline == ':' || *cmdline == ';')
	{
		ft_dprintf(ms->error_fd, CRED"minishell: unsupported token '%c'\n"RESET,
			*cmdline);
		purger_lexqueue(ms->file_lex);
		ms->error_code = 2;
		return (true);
	}
	return (false);
}

bool	validate_lexqueue_before_core(t_data *ms, char *str,
										enum e_nodetype type, bool *has_cmd)
{
	if (type <= nt_piped_cmd)
		*has_cmd = true;
	if (type >= nt_pipe && type <= nt_AND)
	{
		if (!*has_cmd)
		{
			ft_dprintf(ms->error_fd, CRED "%ssyntax error before token '%s': \
missing operand\n" RESET, MINI, str);
			purger_lexqueue(ms->file_lex);
			ms->error_code = 2;
			return (false);
		}
		*has_cmd = false;
	}
	return (true);
}

bool	validate_lexqueue_before(t_data *ms)
{
	enum e_nodetype	type;
	char			*str;
	int				i;
	bool			has_cmd;

	has_cmd = false;
	i = q_getsize(ms->file_lex);
	while (i--)
	{
		str = q_get(ms->file_lex, q_getsize(ms->file_lex) - 1 - i);
		type = get_node_type(ms, str);
		if (!validate_lexqueue_before_core(ms, str, type, &has_cmd))
			return (false);
	}
	return (true);
}

bool	validate_lexqueue(t_data *ms)
{
	enum e_nodetype	type;
	char			*laststr;

	if (!validate_lexqueue_before(ms))
		return (false);
	if (q_getsize(ms->file_lex) > 0)
	{
		laststr = q_get(ms->file_lex, q_getsize(ms->file_lex) - 1);
		type = get_node_type(ms, laststr);
		if (type >= nt_infile && type <= nt_AND)
		{
			ft_dprintf(ms->error_fd, CRED "%ssyntax error after token '%s': \
missing operand\n" RESET, MINI, laststr);
			purger_lexqueue(ms->file_lex);
			ms->error_code = 2;
			return (false);
		}
	}
	return (true);
}
