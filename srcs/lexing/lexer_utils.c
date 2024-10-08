/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 01:29:32 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/10 00:07:16 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_debug_print_outstr(t_data *ms, char *outstr)
{
	if (ms->debug_mode >= 2)
		ft_dprintf(ms->debug_fd, CORANGE "  get_string returns: '%s'\n" RESET,
			outstr);
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

void	if_debug_print_lex_queue(t_data *ms)
{
	if (ms->debug_mode > 0)
	{
		ft_dprintf(ms->file_lex->print_fd, CORANGE " ");
		queue_print(ms->file_lex, false,
			(t_q_prn_elem_fct)print_queue_node, ms);
		ft_dprintf(ms->file_lex->print_fd, RESET);
	}
}

void	print_queue_node(char *str, t_data *ms)
{
	ft_dprintf(ms->debug_fd, "'%s'", str);
}

void	purger_lexqueue(t_queue *q)
{
	while (q_getsize(q) > 0)
		free(dequeue(q));
}
