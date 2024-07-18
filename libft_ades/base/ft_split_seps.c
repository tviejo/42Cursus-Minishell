/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_seps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:04:40 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/06/11 14:27:14 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

/* Renvoie la position du prochain caractère séparateur (appartenant à
 * l'ensemble sepcharset) dans la chaine str (si not_sep = false).
 * Si not_sep = true, renvoie la position du prochain caratère n'appartenant pas
 * à l'ensemble sepcharset.
*/
char	*find_sep(const char *str, const char *sepcharset, bool not_sep)
{
	const char	*seps;

	while (*str)
	{
		seps = sepcharset;
		while (*seps && *seps != *str)
			seps++;
		if (not_sep ^ (*seps != 0))
			return ((char *)str);
		str++;
	}
	return ((char *)str);
}

/* Renvoie le début de la prochaine chaine (passe les séparateurs au début)
 * jusqu'au séparateur suivant: la longeur de la chaine est écrite dans *len.
*/
char	*getstr(const char *str, const char *sepcharset, int *len)
{
	char	*start;

	start = find_sep(str, sepcharset, FIND_NOT_SEP);
	*len = find_sep(start, sepcharset, FIND_SEP) - start;
	return (start);
}

static char	**malloc_tab(const char *str, const char *separators, int *nb_elem)
{
	const char	*s;
	int			len;

	s = str;
	*nb_elem = 0;
	len = 0;
	while (*s)
	{
		s = getstr(s + len, separators, &len);
		if (*s)
			(*nb_elem)++;
	}
	return (malloc((*nb_elem + 1) * sizeof(char *)));
}

static char	**set_tab(char **tab, const char *str, const char *separators,
	int nb_elem)
{
	const char	**tab0 = (const char **)tab;
	int			i;
	int			slen;

	i = 0;
	slen = 0;
	while (i < nb_elem)
	{
		str = getstr(str + slen, separators, &slen);
		tab[i] = malloc(slen + 1);
		if (!tab[i])
		{
			while (*tab)
				free(*tab++);
			free(tab0);
			return (NULL);
		}
		ft_strlcpy(tab[i], str, slen + 1);
		i++;
	}
	tab[i] = 0;
	return (tab);
}

/* Decoupe une chaine en sous chaines et les renvoie dans un tableau
 * [in]  'separators': ensemble des car separateurs de chaine. 
 * [out] 'nbelems': (si non NULL), nombre de sous chaines trouvees.
 * NB: le tableau est alloue en memoire. Appeler ft_split_free() pour liberer.
*/
char	**ft_split_seps(const char *str, const char *separators, int *nbelems)
{
	int		nb_elem;
	char	**tab;

	if (nbelems)
		*nbelems = 0;
	tab = malloc_tab(str, separators, &nb_elem);
	if (!tab)
		return (NULL);
	if (!set_tab(tab, str, separators, nb_elem))
		return (NULL);
	if (nbelems)
		*nbelems = nb_elem;
	return (tab);
}
