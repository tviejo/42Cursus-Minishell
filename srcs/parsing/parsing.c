/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:19:40 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/22 07:20:44 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_tree(t_parsing *p, t_cmdtree **node)
{
	if (getsize(p->pile_npi))
	{
		*node = pop(p->pile_npi);
		(*node)->nb_command = 0;
		if ((*node)->type == nt_command)
			(*node)->nb_command++;
		else
			(*node)->nb_command += build_tree(p, &(*node)->right);
		if ((*node)->type >= nt_pipe)
			(*node)->nb_command += build_tree(p, &(*node)->left);
		return ((*node)->nb_command);
	}
	return (0);
}

void	process_close_parenth(t_parsing *p)
{
	t_cmdtree	*ope;

	while (getsize(p->pile_ope))
	{
		ope = pop(p->pile_ope);
		//print_node(ope, p->operators);
		if (ope->type == nt_open_parenth)
			return ;
		push(p->pile_npi, ope);
	}
}

void	process_operator(t_parsing *p, t_cmdtree *ope)
{
	const int	priority = get_node_priority(p, ope);

	while (gettop(p->pile_ope))
	{
		if (priority <= get_node_priority(p, gettop(p->pile_ope)))
			push(p->pile_npi, pop(p->pile_ope));
		else
			break ;
	}
	push(p->pile_ope, ope);
}

void	depiler_operateurs_restants(t_parsing *p)
{
	t_cmdtree	*ope;

	while (gettop(p->pile_ope))
	{
		ope = pop(p->pile_ope);
		if (ope->type != nt_open_parenth)
			push(p->pile_npi, ope);
	}
}

t_cmdtree	*parse_cmdline(t_parsing *p, char *cmdline)
{
	char **const	words = ft_split(cmdline, ' ');
	t_cmdtree		*node;

	p->splited_words = words;
	if (words == NULL)
		return (NULL);
	p->cmdtree = NULL;
	while (*words)
	{
		//ft_printf("*words = %s\n", *words);
		/*stack_print(p->pile_npi, true, (t_print_elem_fct)print_node,
			p->operators);
		stack_print(p->pile_ope, true, (t_print_elem_fct)print_node,
			p->operators);*/
		node = new_node(p, (char ***)&words);
		if (node == NULL)
			return (NULL);
		if (node->type == nt_command)
			push(p->pile_npi, node);
		else if (node->type == nt_open_parenth)
			push(p->pile_ope, node);
		else if (node->type == nt_close_parenth)
			process_close_parenth(p);
		else
			process_operator(p, node);
	}
	depiler_operateurs_restants(p);
	stack_print(p->pile_npi, false, (t_print_elem_fct)print_node, p->operators);
	build_tree(p, &p->cmdtree);
	return (p->cmdtree);
}
