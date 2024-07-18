/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_nbr.h"

int	get_digit(char c)
{
	int	digit;

	digit = -1;
	if (c >= '0' && c <= '9')
		digit = c - '0';
	if (c >= 'a' && c <= 'z')
		digit = c - 'a' + 10;
	if (c >= 'A' && c <= 'Z')
		digit = c - 'A' + 10;
	return (digit);
}

int	str2int(const char *str, int base, char **pend)
{
	int	num;
	int	signe;
	int	digit;

	num = 0;
	signe = 1;
	while (*str == '+' || *str == '-'
		|| *str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
	{
		if (*str == '-')
			signe = -signe;
		str++;
	}
	digit = get_digit(*str);
	while (digit >= 0 && digit < base)
	{
		num = base * num + digit;
		digit = get_digit(*++str);
	}
	if (pend)
		*pend = (char *)str;
	return (num * signe);
}

// Déjà défini dans libft
/*int	ft_atoi(const char *str)
{
	return (str2int(str, 10, 0));
}*/

void	test_itoa_str2int(void)
{
	char		buffer[34];
	char		buffer2[34];
	const char	*snum = "7aFceBDd";

	ft_printf(">>> Tests des fonctions ft_itoa et str2int\n");
	ft_printf(" 0 =  %s$\n", ft_itoa(0, 10, 0, buffer));
	ft_printf("-1 = %s$\n", ft_itoa(-1, 10, 0, buffer));
	ft_printf("max int =  %s$\n", ft_itoa(0x7fffffff, 10, 0, buffer));
	ft_printf("min int = %s$\n", ft_itoa((int)0x80000000, 10, 0, buffer));
	ft_printf("1234567890 = [hexa] %s$\n", ft_itoa(1234567890, 16, 0, buffer));
	ft_printf("retour en base 10 : %s$\n",
		ft_itoa(str2int(buffer, 16, 0), 10, 0, buffer));
	ft_printf("%s : base10: %s  base16: %s\n", snum,
		ft_itoa(str2int(snum, 16, 0), 10, 0, buffer),
		ft_itoa(str2int(snum, 16, 0), 16, 0, buffer2));
}
