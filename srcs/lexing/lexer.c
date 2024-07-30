/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 02:00:11 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/30 17:19:34 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WORD_MAXLEN 511

/* Recupère un element de la ligne de commande (fin de la chaine identifiée par
 * un des element du tableau de separateurs 'seps')
*/
char	*get_string(t_data *ms, char **cmdline, char *outstr, int maxlen)
{
	char**const	seps = ms->separators;
	char		*str;
	int			i;

	str = *cmdline;
	while (*str)
	{
		i = 0;
		while (seps[i] && (ft_strncmp(str, seps[i], ft_strlen(seps[i])) != 0))
			i++;
		if (seps[i] != NULL)
		{
			if (str == *cmdline)
				str += ft_strlen(seps[i]);
			break ;
		}
		else
			str++;
	}
	if (str - *cmdline + 1 > maxlen)
		return (NULL);
	ft_strlcpy(outstr, *cmdline, str - *cmdline + 1);
	*cmdline = str;
	if (ms->debug_mode > 0)
		ft_printf("  get_string returns: %s\n", outstr);
	return (outstr);
}

bool	lex_quote(enum e_quote_state *quote_state, char *cmdline,
					char **newcmdline)
{
	if (*cmdline == '\'')
	{
		if (*quote_state == simple_quote)
			*quote_state = no_quote;
		else if (*quote_state == double_quote)
			*newcmdline = ft_straddchar(*newcmdline, '\'');
		else
			*quote_state = simple_quote;
		return (true);
	}
	else if (*cmdline == '"')
	{
		if (*quote_state == double_quote)
			*quote_state = no_quote;
		else if (*quote_state == simple_quote)
			*newcmdline = ft_straddchar(*newcmdline, '"');
		else
			*quote_state = double_quote;
		return (true);
	}
	return (false);
}

bool	lex_bslash_n_dollar(t_data *ms,  enum e_quote_state quote_state,
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

void	lex_others(t_data *ms,  enum e_quote_state quote_state,
							char **cmdline, char **newcmdline)
{
	static char			word[WORD_MAXLEN + 1];
	enum e_nodetype		ntype;

	if (quote_state == no_quote)
	{
		get_string(ms, cmdline, word, WORD_MAXLEN);
		ntype = get_node_type(ms, word);
		if (ntype != nt_command)
			*newcmdline = ft_straddchar(*newcmdline, ' ');
		*newcmdline = ft_stradd(*newcmdline, word);
		if (ntype != nt_command)
			*newcmdline = ft_straddchar(*newcmdline, ' ');
	}
	else
		*newcmdline = ft_straddchar(*newcmdline, *(*cmdline)++);
}

char	*lexer(t_data *ms, char *cmdline)
{
	char				*newcmdline;
	enum e_quote_state	quote_state;

	newcmdline = NULL;
	quote_state = no_quote;
	while (*cmdline)
	{
		if (lex_quote(&quote_state, cmdline, &newcmdline))
			cmdline++;
		else if (lex_bslash_n_dollar(ms, quote_state, &cmdline, &newcmdline))
			;
		else
			lex_others(ms, quote_state, &cmdline, &newcmdline);
	}
	return (newcmdline);
}
