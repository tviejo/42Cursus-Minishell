/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:03:59 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/20 16:05:05 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Supprime et libère la mémoire de l’élément passé en
 * paramètre, et de tous les éléments qui suivent, à
 * l’aide de ’del’ et de free(3)
 * Enfin, le pointeur initial doit être mis à NULL.
*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;
	t_list	*next;

	list = *lst;
	while (list)
	{
		next = list->next;
		ft_lstdelone(list, del);
		list = next;
	}
	*lst = NULL;
}
