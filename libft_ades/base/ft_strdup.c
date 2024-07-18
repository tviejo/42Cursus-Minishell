/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:04:46 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/20 16:10:17 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*clone;
	int		slen;

	slen = ft_strlen(s);
	clone = malloc(slen + 1);
	if (clone == NULL)
		return (NULL);
	ft_strlcpy(clone, s, slen + 1);
	return (clone);
}
