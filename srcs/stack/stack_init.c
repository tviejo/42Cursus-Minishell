/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 04:38:22 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/20 04:57:22 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Pile générique (éléments de type void *) mise en oeuvre à l'aide d'un tableau
*/

#include "stack.h"

t_stack	*stack_new(int capacity)
{
	t_stack *const	stack = malloc(sizeof(t_stack));

	if (stack)
	{
		stack->elems = malloc(capacity * sizeof(void *));
		if (stack->elems == NULL)
			return (free(stack), NULL);
		stack->nb_max_elems = capacity;
		stack->top = stack->elems - 1;
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
