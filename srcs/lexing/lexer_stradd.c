/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:41:37 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/26 19:55:34 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen2(const char *str)
{
	const char	*s = str;

	if (!str)
		return (0);
	while (*s)
		s++;
	return (s - str);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	int		s1len;
	int		s2len;
	char	*concat;

	s1len = ft_strlen2(s1);
	s2len = ft_strlen2(s2);
	concat = malloc(s1len + s2len + 1);
	if (concat == NULL)
		return (NULL);
	concat[0] = '\0';
	if (s1)
		ft_strlcpy(concat, s1, s1len + 1);
	if (s2)
		ft_strlcpy(concat + s1len, s2, s2len + 1);
	return (concat);
}

/* Ajoute 'toadd' à la chaine 's' et renvoie la nouvelle chaine formée.
 * Attention: à la difference de strjoin, le 's' (initial) sera désalloué;
 * il doit donc obligatoirement avoir été préalablement malloc (sauf si NULL).
 * La valeur renvoyée peut etre vue comme la nouvelle adresse de 's' après
 * ajout de 'toadd'.
*/
char	*ft_stradd(char *s, char const *toadd)
{
	char	*concat;

	concat = ft_strjoin2(s, toadd);
	if (concat != NULL && s != NULL)
		free(s);
	return (concat);
}

char	*ft_straddchar(char *s, char const c)
{
	const char	toadd[] = {c, '\0'};

	return (ft_stradd(s, toadd));
}
