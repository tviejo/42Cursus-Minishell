/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:04:11 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/20 16:05:41 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/* Idem ft_lstnew avec application de f sur content.
 * Si f(content) retourne NULL alors que content <> NULL, on considère qu'il
 * y a eu une erreur d'allocation mémoire pendant l'execution de f et on
 * retourne NULL.
*/
static t_list	*ft_lstnew_f(void *content, void *(*f)(void *))
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (elem == NULL)
		return (NULL);
	elem->content = f(content);
	if (elem->content == NULL && content != NULL)
	{
		free(elem);
		return (NULL);
	}
	elem->next = NULL;
	return (elem);
}

/* Itère sur la liste ’lst’ et applique la fonction
 * ’f ’au contenu de chaque élément. Crée une nouvelle
 * liste résultant des applications successives de
 * ’f’. La fonction ’del’ est là pour détruire le
 * contenu d’un élément si nécessaire.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*lst2;

	if (lst == NULL)
		return (NULL);
	new = ft_lstnew_f(lst->content, f);
	if (new == NULL)
		return (NULL);
	lst2 = new;
	while (lst->next)
	{
		lst = lst->next;
		lst2->next = ft_lstnew_f(lst->content, f);
		if (lst2->next == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		lst2 = lst2->next;
	}
	return (new);
}
