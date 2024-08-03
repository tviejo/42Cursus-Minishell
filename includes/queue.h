/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 02:20:29 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/03 00:31:33 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* File générique (éléments de type void *) mise en oeuvre à l'aide d'un tableau
*/

#ifndef QUEUE_H
# define QUEUE_H

# include "../libft/libft.h"
# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>

typedef void	(*t_q_prn_elem_fct)(void *elm, void *ctx);

typedef struct s_queue
{
	int					nb_max_elems;
	int					nb_elems;
	void				**in;
	void				**out;
	void				**elems;
	char				*name;
	t_q_prn_elem_fct	print_elem_fct;
	void				*print_elem_ctxarg;
	int					print_fd;
}	t_queue;

t_queue	*queue_new(int capacity, char *name, int print_fd);
void	queue_delete(t_queue *s);
void	queue_print(t_queue *s, bool reverse, t_q_prn_elem_fct fct, void *ctx);
void	enqueue(t_queue *s, void *obj);
void	*dequeue(t_queue *s);
void	*q_getout(t_queue *s);
void	*q_get(t_queue *q, int pos);
int		q_getsize(t_queue *s);

#endif