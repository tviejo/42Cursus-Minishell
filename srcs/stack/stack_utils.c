/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 04:38:22 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/03 00:56:43 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Pile générique (éléments de type void *) mise en oeuvre à l'aide d'un tableau
*/

#include "stack.h"

t_stack	*stack_new(int capacity, char *name, int print_fd)
{
	t_stack *const	stack = malloc(sizeof(t_stack));

	if (stack)
	{
		stack->elems = malloc(capacity * sizeof(void *));
		if (stack->elems == NULL)
			return (free(stack), NULL);
		stack->nb_max_elems = capacity;
		stack->top = stack->elems - 1;
		stack->name = name;
		stack->print_fd = print_fd;
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

void	stack_print_elem(t_stack *s, void ***elm, bool from_top)
{
	void *const				ctx = s->print_elem_ctxarg;
	const t_print_elem_fct	print_elem = s->print_elem_fct;

	ft_dprintf(s->print_fd, ",");
	if (from_top)
		print_elem(*(*elm)--, ctx);
	else
		print_elem(*(*elm)++, ctx);
}

void	stack_print(t_stack *s, bool from_top,
					t_print_elem_fct print_elem, void *ctx)
{
	void	**elm;

	s->print_elem_fct = print_elem;
	s->print_elem_ctxarg = ctx;
	ft_dprintf(s->print_fd, "[pile '%s']: ", s->name);
	if (getsize(s) == 0)
		ft_dprintf(s->print_fd, "<vide>");
	else if (from_top)
	{
		elm = s->top;
		if (elm >= s->elems)
			print_elem(*elm--, ctx);
		while (elm >= s->elems)
			stack_print_elem(s, &elm, from_top);
	}
	else
	{
		elm = s->elems;
		if (elm <= s->top)
			print_elem(*elm++, ctx);
		while (elm <= s->top)
			stack_print_elem(s, &elm, from_top);
	}
	ft_dprintf(s->print_fd, "\n");
}
