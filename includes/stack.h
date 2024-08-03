/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 04:48:41 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/03 00:52:40 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Pile générique (éléments de type void *) mise en oeuvre à l'aide d'un tableau
*/

#ifndef STACK_H
# define STACK_H

# include "../libft/libft.h"
# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>

typedef void	(*t_print_elem_fct)(void *elm, void *ctx);

typedef struct s_stack
{
	int					nb_max_elems;
	void				**top;
	void				**elems;
	char				*name;
	t_print_elem_fct	print_elem_fct;
	void				*print_elem_ctxarg;
	int					print_fd;
}	t_stack;

t_stack	*stack_new(int capacity, char *name, int print_fd);
void	stack_delete(t_stack *s);
void	stack_print(t_stack *s, bool from_top, t_print_elem_fct fct, void *ctx);
void	push(t_stack *s, void *obj);
void	*pop(t_stack *s);
void	*gettop(t_stack *s);
int		getsize(t_stack *s);

#endif