/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double2str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_str_nbr.h"
#include "ft_math.h"

/* Conversion de la partie fractionnaire d'un double <nbr> dans la base
 * <base> avec <digits> chiffres significatifs écrits dans <buf>
 * Attention obligatoire : 1.0 <= nbr < base et 2 <= base <= 36
 * Appelé par double2str(), renvoie la position après le dernier char écrit.
*/
char	*dblfract2str(double nbr, int base, int digits, char *buf)
{
	static const char		*digit = "0123456789abcdefghijklmnopqrstuvwxyz";
	static const uint64_t	fractmask = 0x000FFFFFFFFFFFFFu;
	const uint64_t			nbr64 = *(uint64_t *)&nbr;
	uint64_t				fract;

	fract = ((nbr64 & fractmask) + (1ul << 52u))
		<< ((int)((nbr64 >> 52u) & 0x7FF) - 1023);
	*buf++ = digit[fract >> 52];
	fract &= fractmask;
	*buf++ = '.';
	if (digits <= 0)
		digits = FTOA_NB_DIGIT_DEFAULT;
	while (fract && digits--)
	{
		fract *= base;
		*buf++ = digit[fract >> 52];
		fract &= fractmask;
	}
	if (buf[-1] == '.')
		*buf++ = '0';
	return (buf);
}

/* Calcule et renvoie la valeur de l'exposant pour la base <base>.
 * Normalise <nbr> ; au retour : 1.0 <= nbr < base
 * Attention : nbr DOIT etre positif
*/
int	dbl_normalize(double *nbr, int base)
{
	const double	fbase = base;
	const double	invfbase = 1.0 / fbase;
	const double	ln2_div_lnb = ft_ln(2.0) / ft_ln(fbase);
	int				expb;

	expb = ((int)((*(uint64_t *)nbr >> 52) & 0x7FF) - 1023) * ln2_div_lnb;
	*nbr /= powerd(fbase, expb);
	while (*nbr >= fbase)
	{
		*nbr *= invfbase;
		expb++;
	}
	while (*nbr < 1.0)
	{
		*nbr *= fbase;
		expb--;
	}
	return (expb);
}

/* Conversion d'un réel double en base <base> avec <digits> chiffres
 * significatifs vers le buffer <buf>. Le nombre est normalisé avant
 * conversion et representé sous forme scientifique (ou autre).
 * Renvoie la position du caractère de fin de chaine suite à la conversion.
 * Si base = -1, donne la representation interne du nombre.
*/
char	*double2str(double nbr, int base, int nbdigits, char *buf)
{
	int		expb;

	if (base == -1)
		return (dblraw2str(nbr, buf));
	if (dblspecialvals(nbr, buf))
		return (buf);
	if (base < 2 || base > 36)
		return (buf);
	if ((int)(*(uint64_t *)&nbr >> 63))
	{
		*buf++ = '-';
		nbr = -nbr;
	}
	expb = dbl_normalize(&nbr, base);
	buf = dblfract2str(nbr, base, nbdigits, buf);
	if (expb != 0)
	{
		*buf++ = '^';
		*buf++ = 'e';
		buf = int2str(expb, base, 0, buf);
	}
	*buf = '\0';
	return (buf);
}

/* Conversion d'un réel double en base <base> avec <digits> chiffres
 * significatifs vers le buffer <buf>. Le nombre est normalisé avant
 * conversion et representé sous forme scientifique (ou autre).
 * Si base = -1, donne la representation interne du nombre.
*/
char	*ft_ftoa(double nbr, int base, int nbdigits, char *buf)
{
	double2str(nbr, base, nbdigits, buf);
	return (buf);
}
