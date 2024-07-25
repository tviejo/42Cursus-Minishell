/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:29 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/25 11:54:11 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_and_or(t_command_tree *tree)
{
	if (tree->type == nt_AND || tree->type == nt_OR)
		return (true);
	return (false);
}
