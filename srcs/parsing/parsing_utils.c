/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 05:27:35 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/23 16:34:45 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_node_priority(t_data *p, t_cmdtree *node)
{
	//ft_printf("node->type = %d\n", node->type);
	return (p->operators[node->type].priority);
}

enum e_nodetype	get_node_type(t_data *p, char *word)
{
	enum e_nodetype	type;

	type = 0;
	while (++type < nt_number_of_nodetype)
	{
		if (ft_strncmp(word, p->operators[type].token, 255) == 0)
			return (type);
	}
	return (nt_command);
}

int	get_nb_args(t_data *p, char **words)
{
	int	nb_args;

	nb_args = 0;
	while (*words && get_node_type(p, *words) == nt_command)
	{
		words++;
		nb_args++;
	}
	return (nb_args);
}

int	fill_cmd_args(t_data *p, char **words, t_cmdtree *cmdnode)
{
	int	nb_args;
	int	i;

	if (cmdnode->type == nt_command)
		nb_args = get_nb_args(p, words);
	else
		nb_args = 1;
	cmdnode->argument = malloc((nb_args + 1) * sizeof(char *));
	i = nb_args;
	cmdnode->argument[i] = NULL;
	while (i-- > 0)
		cmdnode->argument[i] = words[i];
	return (nb_args);
}

t_cmdtree	*new_node(t_data *p, char ***words)
{
	static t_cmdtree		open_parenthesis = {.type = nt_open_parenth};
	static t_cmdtree		close_parenthesis = {.type = nt_close_parenth};
	t_cmdtree				*node;
	const enum e_nodetype	type = get_node_type(p, **words);

	if (type == nt_open_parenth)
		return ((*words)++, &open_parenthesis);
	if (type == nt_close_parenth)
		return ((*words)++, &close_parenthesis);
	node = malloc(sizeof(t_cmdtree));
	if (node == NULL)
		return (ft_putstr_fd("[new_node] malloc fails !\n", 2), NULL);
	node->type = type;
	node->argument = NULL;
	node->left = NULL;
	node->right = NULL;
	if (node->type == nt_command)
		(*words) += fill_cmd_args(p, *words, node);
	else if (node->type < nt_pipe)
		(*words) += fill_cmd_args(p, *words + 1, node) + 1;
	else
		(*words)++;
	return (node);
}
