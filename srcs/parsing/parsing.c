/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:19:40 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/03 17:08:24 by ade-sarr         ###   ########.fr       */
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
int	build_tree(t_data *p, t_cmdtree **node, bool piped_cmd)
{
	t_cmdtree	*n;

	if (getsize(p->pile_npi))
	{
		n = pop(p->pile_npi);
		*node = n;
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
			n->nb_command += build_tree(p, &n->right, piped_cmd);
		if (n->type >= nt_pipe)
			n->nb_command += build_tree(p, &n->left,
					piped_cmd || n->type == nt_pipe);
		return (n->nb_command);
	}
	return (0);
}

void	process_close_parenth(t_data *p)
{
	t_cmdtree	*ope;
	t_cmdtree	*lastope;

	lastope = NULL;
	while (getsize(p->pile_ope))
	{
		ope = pop(p->pile_ope);
		if (ope->type == nt_open_parenth)
			break ;
		push(p->pile_npi, ope);
		lastope = ope;
	}
	if (lastope)
		lastope->subshell = ss_YES;
}

void	process_operator(t_data *p, t_cmdtree *ope)
{
	const int	priority = get_node_priority(p, ope);

	if (priority == PRI_REDIR)
	{
		push(p->pile_ope, ope);
		return ;
	}
	while (gettop(p->pile_ope))
	{
		if (priority <= get_node_priority(p, gettop(p->pile_ope)))
			push(p->pile_npi, pop(p->pile_ope));
		else
			break ;
	}
	push(p->pile_ope, ope);
}

void	depiler_operateurs_restants(t_data *p)
{
	t_cmdtree	*ope;

	while (gettop(p->pile_ope))
	{
		ope = pop(p->pile_ope);
		if (ope->type != nt_open_parenth)
			push(p->pile_npi, ope);
	}
}

t_cmdtree	*parser(t_data *p)
{
	t_cmdtree	*node;
	char		*str;

	p->cmdtree = NULL;
	while (q_getsize(p->file_lex) > 0)
	{
		str = dequeue(p->file_lex);
		node = new_node(p, str);
		free(str);
		if (node == NULL)
			return (exit_parser(p), NULL);
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
	if_debug_print_npi_stack(p);
	build_tree(p, &p->cmdtree, false);
	return (p->cmdtree);
}
