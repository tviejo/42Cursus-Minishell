/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:04:51 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/17 16:04:40 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/* Allocates (with malloc(3)) and returns a new
 * string, which is the result of the concatenation
 * of ’s1’ and ’s2’.
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1len;
	int		s2len;
	char	*concat;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	concat = malloc(s1len + s2len + 1);
	if (concat == NULL)
		return (NULL);
	ft_strlcpy(concat, s1, s1len + 1);
	ft_strlcpy(concat + s1len, s2, s2len + 1);
	return (concat);
}
