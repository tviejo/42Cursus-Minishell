/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 01:29:32 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/03 16:25:57 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_debug_print_outstr(t_data *ms, char *outstr)
{
	if (ms->debug_mode >= 2)
		ft_dprintf(ms->debug_fd, "  get_string returns: '%s'\n", outstr);
}

/* Recupère un element de la ligne de commande (fin de la chaine identifiée par
 * un des element du tableau de separateurs 'seps')
 */
char	*get_token(t_data *ms, char **cmdline, char *outstr, int maxlen)
{
	char **const	seps = ms->separators;
	char			*str;
	int				i;

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
	if_debug_print_outstr(ms, outstr);
	return (outstr);
}

/*enum e_quote_state	end_quote(t_data *ms, char **newcmdline)
{
	if (*newcmdline)
	{
		enqueue(ms->file_lex, *newcmdline);
		*newcmdline = NULL;
	}
	return (no_quote);
}*/
void	print_queue_node(char *str, t_data *ms)
{
	ft_dprintf(ms->debug_fd, "'%s'", str);
}

void	purger_lexqueue(t_queue *q)
{
	while (q_getsize(q) > 0)
		free(dequeue(q));
}

void	validate_lexqueue(t_data *ms)
{
	enum e_nodetype	type;
	char			*laststr;

	if (q_getsize(ms->file_lex) > 0)
	{
		laststr = q_get(ms->file_lex, q_getsize(ms->file_lex) - 1);
		type = get_node_type(ms, laststr);
		if (type >= nt_infile && type <= nt_AND)
		{
			ft_dprintf(ms->error_fd, "%ssyntax error after token '%s': \
missing operand\n", MINI, laststr);
			purger_lexqueue(ms->file_lex);
			ms->error_code = 1;
		}
	}
}
