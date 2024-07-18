/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:42:58 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/02/25 21:43:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Variante de ft_strlcpy() : renvoie la longueur copiée
*/
unsigned int	ft_strlencpy(char *dest, const char *src, unsigned int size)
{
	int	n;
	int	l;

	l = 0;
	if (size > 0)
	{
		n = size - 1;
		while (*src && n)
		{
			*dest++ = *src++;
			n--;
			l++;
		}
		*dest = '\0';
	}
	return (l);
}

/* Copie <src> dans <dest> et renvoie la longueur de <dest>
*/
unsigned int	ft_strcpylen(char *dest, const char *src)
{
	int	l;

	l = 0;
	while (*src)
	{
		*dest++ = *src++;
		l++;
	}
	*dest = '\0';
	return (l);
}
