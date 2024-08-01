/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:02:09 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/01 13:02:44 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	strlenpro(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*join_with_space(char *str1, char *str2)
{
	char	*return_str;
	int		i;
	int		j;

	return_str = malloc(sizeof(char) * (strlenpro(str1) + strlenpro(str2) + 2));
	i = 0;
	j = 0;
	while (str1 != NULL && str1[i])
	{
		return_str[j] = str1[i];
		i++;
		j++;
	}
	return_str[j] = ' ';
	j++;
	i = 0;
	while (str2[i])
	{
		return_str[j] = str2[i];
		i++;
		j++;
	}
	free(str1);
	return_str[j] = '\0';
	return (return_str);
}
