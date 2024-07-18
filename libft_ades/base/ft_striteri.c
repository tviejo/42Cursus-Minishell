/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:04:49 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/20 16:50:55 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Applique la fonction ’f’ à chaque caractère de la
 * chaîne de caractères transmise comme argument,
 * et en passant son index comme premier argument.
 * Chaque caractère est transmis par adresse à ’f’
 * afin d’être modifié si nécessaire.
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (*s)
		f(i++, s++);
}
