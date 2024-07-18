/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:37:20 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/20 16:56:50 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/* Applique la fonction ’f’ à chaque caractère de
 * la chaîne de caractères ’s’, passant son index
 * comme premier argument et le caractère lui-même
 * comme second argument. Une nouvelle chaîne de
 * caractères est créée (avec malloc(3)), résultant
 * des applications successives de ’f’.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	result = malloc(ft_strlen(s) + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		result[i] = f(i, *s++);
		i++;
	}
	result[i] = '\0';
	return (result);
}
