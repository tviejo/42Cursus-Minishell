/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:05:13 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/20 16:14:12 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/* Alloue (avec malloc(3)) et retourne une chaîne de
 * caractères issue de la chaîne ’s’.
 * Cette nouvelle chaîne commence à l’index ’start’ et
 * a pour taille maximale ’len’.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	const size_t	slen = ft_strlen(s);
	size_t			sublen;
	char			*sub;

	sublen = len;
	if (start >= slen)
		sublen = 0;
	else if (slen - start < len)
		sublen = slen - start;
	sub = malloc(sublen + 1);
	if (sub == NULL)
		return (NULL);
	if (sublen == 0)
		*sub = '\0';
	else
		ft_strlcpy(sub, s + start, sublen + 1);
	return (sub);
}
