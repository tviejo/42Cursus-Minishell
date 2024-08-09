/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:15:26 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/09 21:19:54 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_swap_env(char **env, int i, int j)
{
	char	*tmp;

	tmp = env[i];
	env[i] = env[j];
	env[j] = tmp;
}

void	print_exp_error(char *str)
{
	ft_dprintf(2, CRED "%s%s: not a valid identifier\n" RESET, MINI, str);
}
