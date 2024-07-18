/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:03:56 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/20 16:04:52 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Ajoute l’élément ’new’ au début de la liste.
*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	ft_lstlast(new)->next = *lst;
	*lst = new;
}
