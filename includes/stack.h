/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 04:48:41 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/20 10:23:18 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Pile générique (éléments de type void *) mise en oeuvre à l'aide d'un tableau
*/

#ifndef STACK_H
# define STACK_H

# include "../libft/libft.h"
# include <stddef.h>
# include <stdlib.h>

typedef struct s_stack
{
	int		nb_max_elems;
	void	**top;
	void	**elems;
}	t_stack;

t_stack				*stack_new(int capacity);
void				stack_delete(t_stack *s);
void				push(t_stack *s, void *obj);
void				*pop(t_stack *s);
void				*gettop(t_stack *s);
int					getsize(t_stack *s);

#endif