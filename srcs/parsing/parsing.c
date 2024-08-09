/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:19:40 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/09 19:37:02 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Construction de l'arbre binaire en dépilant tous les éléments de pile_npi
 * (npi comme notation polonaise inversée). Chaque noeud (t_cmdtree) représente
 * soit une commande (type = nt_command ou nt_piped_cmd), soit une "opération" :
 *   - une redirection ('<', '<<', '>', '>>', argument[0] = "nom de fichier
 * ou delimiter"),
 *   - un pipe '|' (type = nt_pipe, argument = NULL),
 *   - un OU logique '||' (type = nt_OR, argument = NULL),
 *   - un ET logique '&&' (type = nt_AND, argument = NULL).
 * 
 * Une commande est toujours une feuille (left = NULL et right = NULL).
 * Un redirection n'a qu'une descendance à droite (left = NULL).
 * Dans les autres cas ('|', '||', '&&'), il y a une descendance des deux cotés.
 * node.nb_command est le nombre de commandes portées par le noeud et sa
 * descendance (left + right).
 * Si une commande se trouve dans la descendance gauche d'au moins un pipe son
 * type est nt_piped_cmd (sinon nt_command).
*/
int	build_tree(t_data *ms, t_cmdtree **node, bool piped_cmd, t_cmdtree *parent)
{
	t_cmdtree	*n;

	if (getsize(ms->pile_npi))
	{
		n = pop(ms->pile_npi);
		*node = n;
		n->parent = parent;
		n->nb_command = 0;
		if (n->subshell == ss_YES && piped_cmd)
			n->subshell = ss_piped;
		if (n->type == nt_command && piped_cmd)
			n->type = nt_piped_cmd;
		if (n->subshell)
			piped_cmd = false;
		if (n->type <= nt_piped_cmd)
			n->nb_command++;
		else
			n->nb_command += build_tree(ms, &n->right, piped_cmd, n);
		if (n->type >= nt_pipe)
			n->nb_command += build_tree(ms, &n->left,
					piped_cmd || n->type == nt_pipe, n);
		return (n->nb_command);
	}
	return (0);
}

void	process_close_parenth(t_data *ms)
{
	t_cmdtree	*ope;
	t_cmdtree	*lastope;
	t_cmdtree	*cmd;

	lastope = NULL;
	while (getsize(ms->pile_ope))
	{
		ope = pop(ms->pile_ope);
		if (ope->type == nt_open_parenth)
			break ;
		push(ms->pile_npi, ope);
		lastope = ope;
	}
	if (lastope)
		lastope->subshell = ss_YES;
	else
	{
		cmd = gettop(ms->pile_npi);
		if (cmd && cmd->argument
			&& ft_strncmp(cmd->argument[0], "exit", 1024) == 0)
			cmd->subshell = true;
	}
}

void	process_operator(t_data *ms, t_cmdtree *ope)
{
	const int	priority = get_node_priority(ms, ope);

	if (priority == PRI_REDIR)
	{
		push(ms->pile_ope, ope);
		return ;
	}
	while (gettop(ms->pile_ope))
	{
		if (priority <= get_node_priority(ms, gettop(ms->pile_ope)))
			push(ms->pile_npi, pop(ms->pile_ope));
		else
			break ;
	}
	push(ms->pile_ope, ope);
}

void	parser_core(t_data *ms, t_cmdtree *node)
{
	if (node->type == nt_command)
		push(ms->pile_npi, node);
	else if (node->type == nt_open_parenth)
		push(ms->pile_ope, node);
	else if (node->type == nt_close_parenth)
		process_close_parenth(ms);
	else
		process_operator(ms, node);
}

t_cmdtree	*parser(t_data *ms)
{
	t_cmdtree	*node;
	char		*str;

	ms->nextcmdpos = 0;
	ms->cmdtree = NULL;
	while (q_getsize(ms->file_lex) > 0)
	{
		str = dequeue(ms->file_lex);
		if (get_node_type(ms, str) == nt_command && ms->nextcmdpos-- > 0)
			continue ;
		node = new_node(ms, str);
		free(str);
		if (node == NULL)
			return (exit_parser(ms), NULL);
		parser_core(ms, node);
	}
	depiler_operateurs_restants(ms);
	if_debug_print_npi_stack(ms);
	build_tree(ms, &ms->cmdtree, false, NULL);
	if (ms->debug_mode > 0)
		print_cmdtree(ms, ms->debug_fd);
	return (ms->cmdtree);
}
