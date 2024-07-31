/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 04:38:22 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/31 18:28:07 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* File générique (éléments de type void *) mise en oeuvre à l'aide d'un tableau
*/

#include "queue.h"

t_queue	*queue_new(int capacity, char *name)
{
	t_queue *const	queue = malloc(sizeof(t_queue));

	if (queue)
	{
		queue->elems = malloc(capacity * sizeof(void *));
		if (queue->elems == NULL)
			return (free(queue), NULL);
		queue->nb_max_elems = capacity;
		queue->in = queue->elems;
		queue->out = queue->elems;
		queue->nb_elems = 0;
		queue->name = name;
	}
	return (queue);
}

void	queue_delete(t_queue *q)
{
	if (q)
	{
		if (q->elems)
			free(q->elems);
		free(q);
	}
}

void	queue_print_elem(t_queue *q, void ***elm, bool reverse)
{
	void *const				ctx = q->print_elem_ctxarg;
	const t_q_prn_elem_fct	print_elem = q->print_elem_fct;

	ft_printf(",");
	if (reverse)
		print_elem(*(*elm)--, ctx);
	else
		print_elem(*(*elm)++, ctx);
	if (*elm >= q->elems + q->nb_max_elems)
		*elm = q->elems;
	else if (*elm < q->elems)
		*elm = q->elems + q->nb_max_elems;
}

void	queue_print(t_queue *s, bool reverse,
					t_q_prn_elem_fct print_elem, void *ctx)
{
	void	**elm;

	s->print_elem_fct = print_elem;
	s->print_elem_ctxarg = ctx;
	ft_printf("[file '%s']: ", s->name);
	if (reverse)
	{
		elm = s->in;
		if (elm != s->out)
			print_elem(*elm--, ctx);
		while (elm != s->out)
			queue_print_elem(s, &elm, reverse);
	}
	else
	{
		elm = s->out;
		if (elm != s->in)
			print_elem(*elm++, ctx);
		while (elm != s->in)
			queue_print_elem(s, &elm, reverse);
	}
	ft_printf("\n");
}
