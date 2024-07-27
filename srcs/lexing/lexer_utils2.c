/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:46:40 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/27 01:52:31 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_int2str(int n)
{
	static char	snum[12];

	*int2str(n, 10, snum) = '\0';
	return (snum);
}
