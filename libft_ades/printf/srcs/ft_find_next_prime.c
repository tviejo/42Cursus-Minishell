/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:09:11 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/02/15 20:34:50 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

int		ft_find_next_prime(int nb);
bool	ft_is_prime(int nb);

bool	ft_is_prime(int nb)
{
	int	i;

	if (nb == 2)
		return (true);
	if ((nb < 2) || !(nb & 1))
		return (false);
	i = 3;
	while ((i < 0xFFFF) && (i * i <= nb))
	{
		if (nb % i == 0)
			return (false);
		i += 2;
	}
	return (true);
}

int	ft_find_next_prime(int nb)
{
	if (nb <= 2)
		return (2);
	nb |= 1;
	while (nb > 0)
	{
		if (ft_is_prime(nb))
			return (nb);
		nb += 2;
	}
	return (0);
}
/*
#include <stdio.h>

int	main (void)
{
	int	nbrs[] = {-12, 0, 1, -2, 2, 4219, 7853, 78989};
	int	i = sizeof(nbrs) / sizeof(int);

	while (--i >= 0)
		printf("find next prime (%i) : %i\n",
			nbrs[i], ft_find_next_prime(nbrs[i]));
	return (0);
}*/
