/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:05:10 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/06/04 02:11:45 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

char	*find_sep_rev(const char *str, const char *sepcharset, bool not_sep)
{
	int			n;
	const char	*seps;

	n = ft_strlen(str);
	str = str + n - 1;
	while (n--)
	{
		seps = sepcharset;
		while (*seps && *seps != *str)
			seps++;
		if (not_sep ^ (*seps != 0))
			return ((char *)str);
		str--;
	}
	return ((char *)str);
}

/* Alloue (avec malloc(3)) et retourne une copie de
 * la chaîne ’s1’, sans les caractères spécifiés
 * dans ’set’ au début et à la fin de la chaîne de
 * caractères.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;

	start = find_sep(s1, set, FIND_NOT_SEP);
	end = find_sep_rev(s1, set, FIND_NOT_SEP);
	return (ft_substr(s1, start - s1, end - start + 1));
}
