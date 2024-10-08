/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:23:46 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/10 18:26:25 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_quote_state	lex_quote_open(enum e_quote_state qstate, char **lexstring)
{
	*lexstring = ft_stradd(*lexstring, "");
	return (qstate);
}

void	enqueue_echo_n(t_data *ms)
{
	enqueue(ms->file_lex, ft_strdup("echo"));
	enqueue(ms->file_lex, ft_strdup("-n"));
	ms->redir_lexstate = rs_NO;
}

void	lex_enqueue(t_data *ms, char *token)
{
	const enum e_nodetype	type = get_node_type(ms, token);
	enum e_nodetype			lasttype;

	if (type >= nt_infile && type <= nt_out_append)
	{
		if (q_getlastin(ms->file_lex))
		{
			lasttype = get_node_type(ms, q_getlastin(ms->file_lex));
			if (lasttype >= nt_pipe && lasttype <= nt_AND)
			{
				ms->redir_lexstate = rs_YES;
			}
		}
	}
	if (type == nt_command)
	{
		if (ms->redir_lexstate == rs_YES)
			ms->redir_lexstate = rs_ARG;
		else if (ms->redir_lexstate == rs_ARG)
			ms->redir_lexstate = rs_NO;
	}
	if (type >= nt_pipe && ms->redir_lexstate == rs_ARG)
		enqueue_echo_n(ms);
	enqueue(ms->file_lex, token);
}

/*void	if_redir_enqueue_echo_n(t_data *ms, enum e_nodetype ntype)
{
	enum e_nodetype	lasttype;

	if (ntype >= nt_infile && ntype <= nt_out_append)
	{
		if (q_getlastin(ms->file_lex))
		{
			lasttype = get_node_type(ms, q_getlastin(ms->file_lex));
			if (lasttype >= nt_pipe && lasttype <= nt_AND)
			{
				ms->redir_after_ope = true;
			}
		}
	}
	if (ntype >= nt_pipe && ms->redir_after_ope)
	{
		enqueue_echo_n(ms);
	}
}*/

/*void	enqueue_token(t_data *ms, char *token, enum e_nodetype ntype)
{
	if_redir_enqueue_echo_n(ms, ntype);
	enqueue(ms->file_lex, ft_strdup(token));
}
*/