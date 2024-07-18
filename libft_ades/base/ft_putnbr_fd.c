/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:04:34 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/21 10:42:01 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void	ft_putnbr_fd(int n, int fd)
{
	char	*snum;

	snum = ft_itoa(n);
	if (snum != NULL)
	{
		ft_putstr_fd(snum, fd);
		free(snum);
	}
}*/

/* Ecrit dans <buf> la representation en base <base> de <nbr>.
 * Attention : n'ajoute PAS de caractere terminal '\0' à la fin.
 * Renvoie un pointeur sur le caractere suivant le dernier chiffre.
*/
static char	*int2str(int nbr, unsigned int base, char *buf)
{
	unsigned int	unbr;
	char			c;

	unbr = nbr;
	if (nbr < 0)
	{
		*buf++ = '-';
		unbr = -nbr;
	}
	if (unbr >= base)
		buf = int2str(unbr / base, base, buf);
	unbr %= base;
	if (unbr < 10)
		c = '0' + unbr;
	else
		c = 'a' + unbr - 10;
	*buf++ = c;
	return (buf);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	snum[12];

	*int2str(n, 10, snum) = '\0';
	ft_putstr_fd(snum, fd);
}
