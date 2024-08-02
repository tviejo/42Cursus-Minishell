/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:55:25 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/02 13:42:25 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_data *exec)
{
	char	pwd[4096];
	char	*pwd2;

	pwd2 = ft_strjoin("PWD=", getcwd(pwd, 4096));
	update_pwd(exec, pwd2);
	ft_dprintf(1, "%s\n", pwd2);
	free(pwd2);
	return (EXIT_SUCCESS);
}
