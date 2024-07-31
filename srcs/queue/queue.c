/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:43:34 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/31 17:24:12 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* File générique (éléments de type void *) mise en oeuvre à l'aide d'un tableau
*/

#include "queue.h"

void	enqueue(t_queue *q, void *obj)
{
	if (q->nb_elems == q->nb_max_elems)
	{
		ft_printf("[file '%s' (%p)][enqueue] Dépassement de capacité \
(max: %d éléments)\n", q->name, q, q->nb_max_elems);
		exit(-1);
	}
	*q->in++ = obj;
	if (q->in >= q->elems + q->nb_max_elems)
		q->in = q->elems;
	q->nb_elems++;
}

void	*dequeue(t_queue *q)
{
	void	*elmout;

	if (q->nb_elems == 0)
	{
		ft_printf("[file '%s' (%p)][dequeue] Erreur file vide !\n", q->name, q);
		exit(-1);
	}
	elmout = *q->out;
	q->out++;
	if (q->out >= q->elems + q->nb_max_elems)
		q->out = q->elems;
	q->nb_elems--;
	return (elmout);
}

void	*q_getout(t_queue *q)
{
	if (q->nb_elems == 0)
		return (NULL);
	return (*q->out);
}

void	*q_get(t_queue *q, int pos)
{
	void	**elm;

	if (q->nb_elems <= pos)
		return (NULL);
	elm = q->out + pos;
	if (elm >= q->elems + q->nb_max_elems)
		elm -= q->nb_max_elems;
	return (*elm);
}

int	q_getsize(t_queue *q)
{
	return (q->nb_elems);
}
