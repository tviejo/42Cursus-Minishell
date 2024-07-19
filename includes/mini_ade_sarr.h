/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ade_sarr.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:17:03 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/19 02:18:06 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_ADE_SARR_H
# define MINI_ADE_SARR_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Pile générique (éléments de type void *) mise en oeuvre à l'aide d'un tableau
*/
typedef struct s_stack
{
	int		nb_max_elems;
	void	**top;
	void	**elems;
}	t_stack;

typedef struct s_operator
{
	char	*token;
	int		priority;
}	t_operator;

typedef struct s_parsing
{
	t_operator			*operators;
	t_stack				*pile;
	struct s_cmdtree	*cmdtree;
}	t_parsing;

t_stack				*stack_new(int capacity);
void				stack_delete(t_stack *s);
void				push(t_stack *s, void *obj);
void				*pop(t_stack *s);

t_parsing			*init_parsing(void);
void				free_parsing(t_parsing *p);
struct s_cmdtree	*parse_cmdline(char *cmdline);
void				print_cmdtree(struct s_cmdtree *cmdtree);

#endif