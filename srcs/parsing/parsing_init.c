/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:19:36 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/08 16:21:12 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NB: unsuported tokens : '&',':',';','!'
*/
bool	init_parsing(t_data *p)
{
	static t_operator	operators[] = {{"cmd", 255}, {"piped", 255},
	{"<", PRI_REDIR}, {"<<", PRI_REDIR}, {">", PRI_REDIR}, {">>", PRI_REDIR},
	{"|", PRI_PIPE}, {"||", PRI_LOGIC}, {"&&", PRI_LOGIC},
	{"(", -1}, {")", -1}, {NULL, 0}};
	static char			*separators[] = {" ", "\t", "\n", "$", "'", "\"", "\\",
		"<<", "<", ">>", ">", "||", "|", "&&", "(", ")",
		"&", ":", ";", "!", NULL};

	p->operators = operators;
	p->separators = separators;
	p->pile_ope = stack_new(1024, "Opérateurs", STDERR_FILENO);
	p->pile_npi = stack_new(2048, "NPI", STDERR_FILENO);
	p->file_lex = queue_new(2048, "lex queue", STDERR_FILENO);
	if (p->pile_ope == NULL || p->pile_npi == NULL)
		return (free_parsing(p), false);
	return (true);
}

void	free_parsing(t_data *p)
{
	if (p)
	{
		stack_delete(p->pile_ope);
		stack_delete(p->pile_npi);
		queue_delete(p->file_lex);
	}
}

void	free_node(t_cmdtree *node)
{
	char	**args;

	if (node)
	{
		if (node->type == nt_here_doc)
			unlink(*node->argument);
		if (node->left)
			free_node(node->left);
		if (node->right)
			free_node(node->right);
		if (node->argument)
		{
			args = node->argument;
			while (*args)
				free(*args++);
			free(node->argument);
		}
		free(node);
	}
}

void	free_cmdtree(t_data *p)
{
	if (p)
	{
		free_node(p->cmdtree);
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
