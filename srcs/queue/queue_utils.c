/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 04:38:22 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/26 10:11:00 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* File générique (éléments de type void *) mise en oeuvre à l'aide d'un tableau
*/

#include "queue.h"

t_queue	*queue_new(int capacity)
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
/*
void	queue_print_elem(void ***elm, bool reverse,
					t_q_prn_elem_fct print_elem, void *ctx)
{
	ft_printf(",");
	if (reverse)
		print_elem(*(*elm)--, ctx);
	else
		print_elem(*(*elm)++, ctx);
	if (*elm > )
}

void	queue_print(t_queue *s, bool reverse,
					t_q_prn_elem_fct print_elem, void *ctx)
{
	void	**elm;

	ft_printf("[file (%p)]: ", s);
	if (reverse)
	{
		elm = s->in;
		if (elm != s->out)
			print_elem(*elm--, ctx);
		while (elm != s->out)
			queue_print_elem(&elm, reverse, print_elem, ctx);
	}
	else
	{
		elm = s->out;
		if (elm != s->in)
			print_elem(*elm++, ctx);
		while (elm != s->in)
			queue_print_elem(&elm, reverse, print_elem, ctx);
	}
	ft_printf("\n");
}
*/