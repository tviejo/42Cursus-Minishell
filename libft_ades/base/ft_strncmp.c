/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:05:01 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/22 16:28:11 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	diff;

	while (n-- && *s1 && *s2)
	{
		diff = *s1++ - *s2++;
		if (diff)
			return (diff);
	}
	if (n == 0)
		return (0);
	return (*s1 - *s2);
}*/

int	ft_strncmp(const char *_s1, const char *_s2, size_t n)
{
	const unsigned char	*s1 = (const unsigned char *)_s1;
	const unsigned char	*s2 = (const unsigned char *)_s2;

	if (n < 1)
		return (0);
	while (*s1 && *s2 && --n)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
