/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 02:00:11 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/09 20:03:34 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define TOKEN_MAXLEN 511

enum e_quote_state	lex_quote_open(enum e_quote_state qstate, char **lexstring)
{
	*lexstring = ft_stradd(*lexstring, "");
	return (qstate);
}

bool	lex_quote(t_data *ms, enum e_quote_state *quote_state, char *cmdline,
		char **lexstring)
{
	(void)ms;
	if (*cmdline == '\'')
	{
		if (*quote_state == simple_quote)
			*quote_state = no_quote;
		else if (*quote_state == double_quote)
			*lexstring = ft_straddchar(*lexstring, '\'');
		else
			*quote_state = lex_quote_open(simple_quote, lexstring);
		return (true);
	}
	else if (*cmdline == '"')
	{
		if (*quote_state == double_quote)
			*quote_state = no_quote;
		else if (*quote_state == simple_quote)
			*lexstring = ft_straddchar(*lexstring, '"');
		else
			*quote_state = lex_quote_open(double_quote, lexstring);
		return (true);
	}
	return (false);
}

bool	lex_bslash_n_dollar(t_data *ms, enum e_quote_state quote_state,
		char **cmdline, char **lexstring)
{
	static char	token[TOKEN_MAXLEN + 1];

	if (**cmdline == '\\' && (*cmdline)[1] && quote_state != simple_quote)
	{
		(*cmdline)++;
		*lexstring = ft_straddchar(*lexstring, *(*cmdline)++);
		return (true);
	}
	else if (**cmdline == '$' && (*cmdline)[1] && quote_state != simple_quote)
	{
		(*cmdline)++;
		if (**cmdline == '?')
		{
			*lexstring = ft_stradd(*lexstring, ft_int2str(ms->error_code));
			(*cmdline)++;
		}
		else
		{
			get_token(ms, cmdline, token, TOKEN_MAXLEN);
			if (get_env_var(ms, token))
				*lexstring = ft_stradd(*lexstring, get_env_var(ms, token));
		}
		return (true);
	}
	return (false);
}

bool	lex_wildcard(t_data *ms, char *token)
{
	char	*filenames;
	char	**splited;
	char	**spnames;

	if (ft_strchr(token, '*') || ft_strchr(token, '?'))
	{
		filenames = find_wildcard(token);
		if (!filenames || *filenames == '\0')
			return (false);
		splited = ft_split(filenames, ' ');
		spnames = splited;
		while (*spnames)
			enqueue(ms->file_lex, ft_strdup(*spnames++));
		ft_free_split(splited);
		free(filenames);
		return (true);
	}
	return (false);
}

void	lex_others(t_data *ms, enum e_quote_state quote_state, char **cmdline,
		char **lexstring)
{
	static char		token[TOKEN_MAXLEN + 1];
	enum e_nodetype	ntype;

	if (quote_state == no_quote)
	{
		get_token(ms, cmdline, token, TOKEN_MAXLEN);
		ntype = get_node_type(ms, token);
		if (ntype != nt_command || *token == ' ' || *token == '\t'
			|| *token == '\n')
		{
			if (*lexstring)
			{
				enqueue(ms->file_lex, *lexstring);
				*lexstring = NULL;
			}
			if (ntype != nt_command)
				enqueue(ms->file_lex, ft_strdup(token));
		}
		else if (!lex_wildcard(ms, token))
			*lexstring = ft_stradd(*lexstring, token);
	}
	else
		*lexstring = ft_straddchar(*lexstring, *(*cmdline)++);
}

bool	lexer(t_data *ms, char *cmdline)
{
	char				*lexstring;
	enum e_quote_state	quote_state;

	lexstring = NULL;
	quote_state = no_quote;
	while (*cmdline)
	{
		if (unsupported_token(ms, cmdline))
			return (false);
		else if (lex_quote(ms, &quote_state, cmdline, &lexstring))
			cmdline++;
		else if (lex_bslash_n_dollar(ms, quote_state, &cmdline, &lexstring))
			;
		else
			lex_others(ms, quote_state, &cmdline, &lexstring);
	}
	if (lexstring)
		enqueue(ms->file_lex, lexstring);
	if_debug_print_lex_queue(ms);
	return (validate_lexqueue(ms));
}
