/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:19:36 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/24 14:59:55 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_parsing(t_data *p)
{
	static t_operator	operators[] = {{"cmd", 255}, {"piped", 255},
	{"<", 2}, {"<<", 2}, {">", 2}, {">>", 2}, {"|", 1},
	{"||", 0}, {"&&", 0}, {"(", -1}, {")", -1}, {NULL, 0}};

	p->operators = operators;
	p->pile_ope = stack_new(1024);
	p->pile_npi = stack_new(2048);
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
	}
}

void	free_node(t_cmdtree *node)
{
	if (node)
	{
		if (node->left)
			free_node(node->left);
		if (node->right)
			free_node(node->right);
		if (node->argument)
			free(node->argument);
		free(node);
	}
}

void	free_cmdtree(t_data *p)
{
	if (p)
	{
		free_node(p->cmdtree);
		if (p->splited_words)
			ft_free_split(p->splited_words);
	}
}
