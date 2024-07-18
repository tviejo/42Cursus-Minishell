/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:13:00 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/28 16:09:02 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include <stdbool.h>

//# define ARR arrangement
//# define CMB combination

double				powerd(double x, int n);
long long			power(long long x, int n);
unsigned long long	factorial(int n);
unsigned long long	arrangement(int p, int n);
unsigned long long	combination(int p, int n);
void				math_test(void);

int					ft_find_next_prime(int nb);
bool				ft_is_prime(int nb);

double				ft_sqrt(double x);
double				ft_ln(double x);
void				test_ft_ln(void);
void				test_ft_ln_vs_log(void);

#endif