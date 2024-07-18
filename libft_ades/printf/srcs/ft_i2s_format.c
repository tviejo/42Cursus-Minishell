/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i2s_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_str_nbr.h"

/* Renseigne une struct t_i2sfmt
 * fmt : format d'affichage pour int2str_ex(), long2str_ex() et ulong2str_ex()
 * base_capit_keep : base ou valeur de retour de i2s_base()
 * len_min_pad_just  : 0 ou valeur de retour de i2s_len() ou i2s_len_j()
 * sep_freq_char_pad : 0 ou valeur de retour de i2s_sep()
*/
void	i2sfmt_set(t_i2s_fmt *fmt, int base_capit_keep,
			int len_min_pad_just, int sep_freq_char_pad)
{
	fmt->base = base_capit_keep & 0xffff;
	fmt->capitdgt = base_capit_keep & 0x1000000;
	fmt->minlen = len_min_pad_just & 0xffff;
	fmt->padchar = (len_min_pad_just >> 16) & 0xff;
	if (fmt->padchar == 0)
		fmt->padchar = ' ';
	fmt->leftjust = len_min_pad_just & 0x1000000;
	fmt->signljust = len_min_pad_just & 0x2000000;
	fmt->sepfreq = sep_freq_char_pad & 0xffff;
	fmt->sepchar = (sep_freq_char_pad >> 16) & 0xff;
	fmt->seppad = sep_freq_char_pad & 0x1000000;
	if (!(base_capit_keep & 0x2000000))
	{
		fmt->strneg = NULL;
		fmt->strpos = NULL;
		fmt->prefix = NULL;
	}
	fmt->printf_precision = 0;
}

/* Renvoie le deuxième argument pour i2sfmt_set(), ft_Xtoa() et XXX2str()
 * base     : base numérique
 * capitdgt : afficher les chiffres (>9) en majuscules
 * keepstr  : conserver valeurs fmt->strneg et fmt->strpos ? (sinon mis à NULL)
*/
int	i2s_base(int base, bool capitdgt, bool keepstr)
{
	return (base | (capitdgt << 24) | (keepstr << 25));
}

/* Renvoie le troisième argument pour i2sfmt_set(), ft_Xtoa() et XXX2str()
 * minlen  : longueur minimale d'écriture
 * padchar : caractère de padding pour arriver à minlen
*/
int	i2s_len(int minlen, char padchar)
{
	return (minlen | (padchar << 16));
}

/* Renvoie le troisième argument pour i2sfmt_set(), ft_Xtoa() et XXX2str()
 * minlen    : longueur minimale d'écriture
 * padchar   : caractère de padding pour arriver à minlen
 * leftjust  : justification à gauche ?
 * signljust : le signe est il justifié à gauche ?
*/
int	i2s_len_j(int minlen, char padchar, bool leftjust, bool signljust)
{
	return (minlen | (padchar << 16) | (leftjust << 24) | (signljust << 25));
}

/* Renvoie le quatrième argument pour i2sfmt_set()
 * sepfreq : ajouter <sepchar> tous les <sepfreq> chiffres
 * sepchar : caractère séparateur des groupes de chiffres
 * seppad  : le padding est il traité comme des chiffres ?
*/
int	i2s_sep(int sepfreq, char sepchar, bool seppad)
{
	return (sepfreq | (sepchar << 16) | (seppad << 24));
}
