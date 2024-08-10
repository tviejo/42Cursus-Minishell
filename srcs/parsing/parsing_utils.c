/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 05:27:35 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/10 00:10:54 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_nodetype	get_node_type(t_data *p, char *word)
{
	enum e_nodetype	type;

	if (p->debug_mode >= 3)
		ft_dprintf(p->debug_fd, CORANGE "[get_node_type] word: '%s'\n" RESET,
			word);
	type = 0;
	while (++type < nt_number_of_nodetype)
	{
		if (ft_strncmp(word, p->operators[type].token, 255) == 0)
			return (type);
	}
	return (nt_command);
}

int	get_nb_args(t_data *p)
{
	int	i;
	int	nb_args;

	nb_args = 0;
	i = 0;
	while (q_get(p->file_lex, i)
		&& get_node_type(p, q_get(p->file_lex, i)) <= nt_out_append)
	{
		if (get_node_type(p, q_get(p->file_lex, i)) == nt_command)
			nb_args++;
		else
			nb_args--;
		i++;
	}
	if (p->debug_mode >= 3)
		ft_printf("nb_args: %d\n", nb_args);
	return (nb_args);
}

/*int	fill_cmd_args(t_data *p, char *arg0, t_cmdtree *cmdnode)
{
	int		nb_args;
	int		i;

	nb_args = 0;
	if (cmdnode->type == nt_command)
		nb_args = get_nb_args(p) + 1;
	else if (q_getsize(p->file_lex) > 0)
		nb_args = 1;
	cmdnode->argument = malloc((nb_args + 1) * sizeof(char *));
	cmdnode->argument[nb_args] = NULL;
	i = -1;
	while (++i < nb_args)
	{
		if (i == 0 && arg0 != NULL)
			cmdnode->argument[0] = ft_strdup(arg0);
		else
			cmdnode->argument[i] = dequeue(p->file_lex);
	}
	return (nb_args);
}*/

void	fill_cmd_args_core(t_data *p, char *arg0, t_cmdtree *cmdnode,
							int nb_args)
{
	int		i;
	int		iarg;
	char	*str;

	i = 0;
	iarg = 0;
	while (iarg < nb_args)
	{
		if (iarg == 0 && arg0 != NULL)
			cmdnode->argument[iarg++] = ft_strdup(arg0);
		else
		{
			str = q_get(p->file_lex, i++);
			if (get_node_type(p, str) == nt_command)
				cmdnode->argument[iarg++] = str;
			else
				i++;
		}
		if (p->debug_mode >= 3)
			ft_printf("arg[%d]= '%s'\n", iarg - 1, cmdnode->argument[iarg - 1]);
	}
	p->nextcmdpos = i + 1;
}

int	fill_cmd_args(t_data *p, char *arg0, t_cmdtree *cmdnode)
{
	int	nb_args;

	nb_args = 0;
	if (cmdnode->type == nt_command)
		nb_args = get_nb_args(p) + 1;
	else if (q_getsize(p->file_lex) > 0)
		nb_args = 1;
	cmdnode->argument = malloc((nb_args + 1) * sizeof(char *));
	cmdnode->argument[nb_args] = NULL;
	if (cmdnode->type == nt_command)
		fill_cmd_args_core(p, arg0, cmdnode, nb_args);
	else
		cmdnode->argument[0] = dequeue(p->file_lex);
	return (nb_args);
}

t_cmdtree	*new_node(t_data *p, char *word)
{
	static t_cmdtree		open_parenthesis = {.type = nt_open_parenth};
	static t_cmdtree		close_parenthesis = {.type = nt_close_parenth};
	t_cmdtree				*node;
	const enum e_nodetype	type = get_node_type(p, word);

	if (type == nt_open_parenth)
		return (&open_parenthesis);
	if (type == nt_close_parenth)
		return (&close_parenthesis);
	node = malloc(sizeof(t_cmdtree));
	if (node == NULL)
		return (ft_putstr_fd(CRED "[new_node] error: malloc fails !\n" RESET,
				p->error_fd), NULL);
	node->type = type;
	node->argument = NULL;
	node->left = NULL;
	node->right = NULL;
	node->subshell = ss_NO;
	if (node->type == nt_command)
		fill_cmd_args(p, word, node);
	else if (node->type < nt_pipe)
		p->nextcmdpos -= fill_cmd_args(p, NULL, node);
	if (node->type == nt_here_doc)
		process_here_doc(node);
	return (p->nextcmdpos--, node);
}
