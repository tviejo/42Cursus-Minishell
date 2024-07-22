/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 04:38:22 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/21 10:08:39 by ade-sarr         ###   ########.fr       */
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

void	stack_print_elem(void ***elm, bool from_top,
					t_print_elem_fct print_elem, void *ctx)
{
	ft_printf(",");
	if (from_top)
		print_elem(*(*elm)--, ctx);
	else
		print_elem(*(*elm)++, ctx);
}

void	stack_print(t_stack *s, bool from_top,
					t_print_elem_fct print_elem, void *ctx)
{
	void	**elm;

	ft_printf("[pile (%p)]: ", s);
	if (from_top)
	{
		elm = s->top;
		if (elm >= s->elems)
			print_elem(*elm--, ctx);
		while (elm >= s->elems)
			stack_print_elem(&elm, from_top, print_elem, ctx);
	}
	else
	{
		elm = s->elems;
		if (elm <= s->top)
			print_elem(*elm++, ctx);
		while (elm <= s->top)
			stack_print_elem(&elm, from_top, print_elem, ctx);
	}
	ft_printf("\n");
}
