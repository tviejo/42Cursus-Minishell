/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:15:39 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/03 02:52:38 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	purger_npistack(t_stack *s)
{
	while (getsize(s) > 0)
		free_node(pop(s));
}

void	process_here_doc(t_cmdtree *node)
{
	char	*redirname;

	if (node->argument && *node->argument)
	{
		redirname = create_here_doc(*node->argument);
		free(*node->argument);
		*node->argument = redirname;
	}
}

/* Quitter proprement sur erreur (malloc fails)
*/
void	exit_parser(t_data *ms)
{
	depiler_operateurs_restants(ms);
	purger_lexqueue(ms->file_lex);
	purger_npistack(ms->pile_npi);
	ms->cmdtree = NULL;
	ms->error_code = 2;
}
