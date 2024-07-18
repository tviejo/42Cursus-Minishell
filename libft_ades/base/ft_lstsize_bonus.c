/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:04:16 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/20 16:05:59 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Compte le nombre d’éléments de la liste.
*/
int	ft_lstsize(t_list *lst)
{
	int	nbelem;

	nbelem = 0;
	while (lst)
	{
		nbelem++;
		lst = lst->next;
	}
	return (nbelem);
}
