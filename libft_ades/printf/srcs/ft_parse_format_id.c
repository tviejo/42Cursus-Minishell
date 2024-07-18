/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format_id.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:50:10 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/29 21:50:10 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_nbr.h"
#include <unistd.h>
#include <stdarg.h>

void	init_format_id(t_format_id *fid)
{
	fid->type = 0;
	fid->left_justify = false;
	fid->prn_pos_sign = false;
	fid->space_pos_val = false;
	fid->zero_padded = false;
	fid->sharp_flag = false;
	fid->min_width = 0;
	fid->max_width = -1;
	fid->base = 0;
}

//const char *const	flags = "-0+ #.";

bool	parse_option(const char **pformat, t_format_id *fid)
{
	const char	*format = *pformat;

	if (*format == '-')
		fid->left_justify = (format++, true);
	else if (*format == '+')
		fid->prn_pos_sign = (format++, true);
	else if (*format == ' ')
		fid->space_pos_val = (format++, true);
	else if (*format == '0')
		fid->zero_padded = (format++, true);
	else if (*format == '#')
		fid->sharp_flag = (format++, true);
	else if (*format == '.')
		fid->max_width = str2int(format + 1, 10, (char **)&format);
	else if (*format == 'B')
		fid->base = str2int(format + 1, 10, (char **)&format);
	else if (*format >= '1' && *format <= '9')
		fid->min_width = str2int(format, 10, (char **)&format);
	if (format != *pformat)
		return (*pformat = format, true);
	else
		return (false);
}

const char	*parse_format_id(const char *format, t_format_id *fid)
{
	const char *const	types = "cspdiuxX%lbfF";

	init_format_id(fid);
	while (*format)
	{
		if (parse_option(&format, fid))
			continue ;
		if (ft_strchr(types, *format))
			return (fid->type = *format, format + 1);
		else
			return (format + 1);
	}
	return (format);
}
