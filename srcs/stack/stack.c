/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:43:34 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/22 07:21:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Pile générique (éléments de type void *) mise en oeuvre à l'aide d'un tableau
*/

#include "stack.h"

void	push(t_stack *s, void *obj)
{
	if (s->top - s->elems >= s->nb_max_elems - 1)
	{
		ft_printf("[stack: %p][push] Dépassement de capacité (max: %d éléments)\
\n", s, s->nb_max_elems);
		exit(-1);
	}
	*++s->top = obj;
}

void	*pop(t_stack *s)
{
	if (s->top < s->elems)
	{
		ft_printf("[stack: %p][pop] Erreur pile vide !\n", s, s->nb_max_elems);
		exit(-1);
	}
	return (*s->top--);
}

void	*gettop(t_stack *s)
{
	if (s->top < s->elems)
		return (NULL);
	return (*s->top);
}

int	getsize(t_stack *s)
{
	return (s->top - s->elems + 1);
}
