/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:04:40 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/06/30 20:18:32 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

char	**ft_split(char const *s, char c)
{
	const char	seps[] = {c, '\0'};

	return (ft_split_seps(s, seps, NULL));
}

void	ft_split_free(char **array)
{
	char	**pstr;

	pstr = array;
	while (*pstr)
	{
		free(*pstr++);
	}
	free(array);
}

int	count_words(const char *str, const char *separators)
{
	int			len;
	int			nb_elem;

	nb_elem = 0;
	len = 0;
	while (*str)
	{
		str = getstr(str + len, separators, &len);
		if (*str)
			nb_elem++;
	}
	return (nb_elem);
}
