/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:19:36 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/31 04:39:14 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_parsing(t_data *p)
{
	static t_operator	operators[] = {{"cmd", 255}, {"piped", 255},
	{"<", PRI_REDIR}, {"<<", PRI_REDIR}, {">", PRI_REDIR}, {">>", PRI_REDIR},
	{"|", PRI_PIPE}, {"||", PRI_LOGIC}, {"&&", PRI_LOGIC},
	{"(", -1}, {")", -1}, {NULL, 0}};
	static char			*separators[] = {" ", "$", "'", "\"", "\\",
		"<<", "<", ">>", ">", "||", "|", "&&", "(", ")", NULL};

	p->operators = operators;
	p->separators = separators;
	p->pile_ope = stack_new(1024, "Opérateurs");
	p->pile_npi = stack_new(2048, "NPI");
	p->file_lex = queue_new(2048, "lex queue");
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
		if (node->left)
			free_node(node->left);
		if (node->right)
			free_node(node->right);
		if (node->argument)
		{
			args = node->argument;
			while (*args++)
				free(*args);
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
		/*if (p->splited_words)
			ft_free_split(p->splited_words);*/
	}
}
