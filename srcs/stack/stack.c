/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:43:34 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/18 18:52:13 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack	*stack_new(int capacity)
{
	t_stack *const	stack = malloc(sizeof(t_stack));

	if (stack)
	{
		stack->elems = malloc(capacity * sizeof(void *));
		if (stack->elems == NULL)
			return (free(stack), NULL);
		stack->nb_max_elems = capacity;
		stack->top = stack->elems;
	}
	return (stack);
}

void	stack_delete(t_stack *s)
{
	if (s)
	{
		if (s->elems)
			free(s->elems);
		free(s);
	}
}

void	push(t_stack *s, void *obj)
{
	if (s->top - s->elems >= s->nb_max_elems)
	{
		ft_printf("[stack: %p][push] Dépassement de capacité (max: %d éléments)\
\n", s, s->nb_max_elems);
		exit(-1);
	}
	*s->top++ = obj;
}

void	*pop(t_stack *s)
{
	if (s->top <= s->elems)
	{
		ft_printf("[stack: %p][pop] Erreur pile vide !\n", s, s->nb_max_elems);
		exit(-1);
	}
	return (*s->top--);
}
