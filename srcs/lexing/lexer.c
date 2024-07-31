/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 02:00:11 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/31 18:02:39 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WORD_MAXLEN 511

bool	lex_quote(t_data *ms, enum e_quote_state *quote_state, char *cmdline,
					char **newcmdline)
{
	if (*cmdline == '\'')
	{
		if (*quote_state == simple_quote)
			*quote_state = end_quote(ms, newcmdline);
		else if (*quote_state == double_quote)
			*newcmdline = ft_straddchar(*newcmdline, '\'');
		else
			*quote_state = simple_quote;
		return (true);
	}
	else if (*cmdline == '"')
	{
		if (*quote_state == double_quote)
			*quote_state = end_quote(ms, newcmdline);
		else if (*quote_state == simple_quote)
			*newcmdline = ft_straddchar(*newcmdline, '"');
		else
			*quote_state = double_quote;
		return (true);
	}
	return (false);
}

bool	lex_bslash_n_dollar(t_data *ms, enum e_quote_state quote_state,
							char **cmdline, char **newcmdline)
{
	static char			word[WORD_MAXLEN + 1];

	if (**cmdline == '\\' && (*cmdline)[1] && quote_state != simple_quote)
	{
		(*cmdline)++;
		*newcmdline = ft_straddchar(*newcmdline, *(*cmdline)++);
		return (true);
	}
	else if (**cmdline == '$' && (*cmdline)[1] && quote_state != simple_quote)
	{
		(*cmdline)++;
		if (**cmdline == '?')
		{
			*newcmdline = ft_stradd(*newcmdline, ft_int2str(ms->error_code));
			(*cmdline)++;
		}
		else
		{
			get_string(ms, cmdline, word, WORD_MAXLEN);
			*newcmdline = ft_stradd(*newcmdline, get_env_var(ms, word));
		}
		return (true);
	}
	return (false);
}

bool	lex_wildcard(t_data *ms, enum e_quote_state quote_state,
							char **cmdline, char **newcmdline)
{
	char		*filenames;
	char		**splited;
	char		**spnames;

	(void)newcmdline;
	if (quote_state == no_quote && **cmdline == '*' && (*cmdline)[1] == '\0')
	{
		filenames = find_wildcard(*cmdline);
		splited = ft_split(filenames, ' ');
		spnames = splited;
		while (*spnames)
			enqueue(ms->file_lex, ft_strdup(*spnames++));
		ft_free_split(splited);
		free(filenames);
		(*cmdline)++;
		return (true);
	}
	return (false);
}

void	lex_others(t_data *ms, enum e_quote_state quote_state,
							char **cmdline, char **newcmdline)
{
	static char			word[WORD_MAXLEN + 1];
	enum e_nodetype		ntype;

	if (quote_state == no_quote)
	{
		get_string(ms, cmdline, word, WORD_MAXLEN);
		ntype = get_node_type(ms, word);
		if (ntype != nt_command || *word == ' ')
		{
			if (*newcmdline)
			{
				enqueue(ms->file_lex, *newcmdline);
				*newcmdline = NULL;
			}
			if (ntype != nt_command)
				enqueue(ms->file_lex, ft_strdup(word));
		}
		else
			*newcmdline = ft_stradd(*newcmdline, word);
	}
	else
		*newcmdline = ft_straddchar(*newcmdline, *(*cmdline)++);
}

void	lexer(t_data *ms, char *cmdline)
{
	char				*newcmdline;
	enum e_quote_state	quote_state;

	newcmdline = NULL;
	quote_state = no_quote;
	while (*cmdline)
	{
		if (lex_quote(ms, &quote_state, cmdline, &newcmdline))
			cmdline++;
		else if (lex_bslash_n_dollar(ms, quote_state, &cmdline, &newcmdline))
			;
		else if (lex_wildcard(ms, quote_state, &cmdline, &newcmdline))
			;
		else
			lex_others(ms, quote_state, &cmdline, &newcmdline);
	}
	if (newcmdline)
		enqueue(ms->file_lex, newcmdline);
}
