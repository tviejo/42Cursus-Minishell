/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i2s_get_i2s_fmt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_str_nbr.h"

char	*get_i2s_prefix(t_format_id *fid, t_i2s_fmt *fmt)
{
	if ((fid->sharp_flag && fid->type == 'x' && fmt->nbr != 0)
		|| fid->type == 'p')
		return ("0x");
	if (fid->sharp_flag && fid->type == 'X' && fmt->nbr != 0)
		return ("0X");
	return (NULL);
}

int	get_base(t_format_id *fid)
{
	if (fid->type == 'i' && fid->base >= 2 && fid->base <= 36)
		return (fid->base);
	if (fid->type == 'b')
		return (2);
	if (fid->type == 'x' || fid->type == 'X' || fid->type == 'p')
		return (16);
	return (10);
}

/* Renseigne la struct 'fmt' (pour fct de conversion entier vers chaine)
 * à partir de la struct 'fid' issue de la chaine de formatteur de printf.
*/
t_i2s_fmt	*get_i2s_fmt(t_format_id *fid, t_i2s_fmt *fmt)
{
	const bool	signed_num = !(fid->type == 'u' || fid->type == 'p'
			|| fid->type == 'x' || fid->type == 'X');
	int			sign_prfix_len;
	char		padchar;
	char		*strpos;

	padchar = ' ';
	if (fid->zero_padded && fid->precision == -1 && !fid->left_justify)
		padchar = '0';
	strpos = NULL;
	if (fid->prn_pos_sign && signed_num)
		strpos = "+";
	if (fid->space_pos_val && signed_num)
		strpos = " ";
	i2sfmt_set(fmt,
		i2s_base(get_base(fid), fid->type == 'X', false),
		i2s_len_j(fid->min_width, padchar, fid->left_justify, padchar == '0'),
		0);
	sign_prfix_len = i2sfmt_setstr(fmt, NULL, strpos, get_i2s_prefix(fid, fmt));
	fmt->printf_precision = fid->precision;
	if (fmt->printf_precision > PRINTF_ARG_BUFFER_SIZE - 4 - sign_prfix_len)
		fmt->printf_precision = PRINTF_ARG_BUFFER_SIZE - 4 - sign_prfix_len;
	if (fmt->minlen > PRINTF_ARG_BUFFER_SIZE - 4)
		fmt->minlen = PRINTF_ARG_BUFFER_SIZE - 4;
	return (fmt);
}
