/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tviejo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:16:44 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/06 16:39:03 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TVIEJO_H
# define MINI_TVIEJO_H

# include "../libft/libft.h"
# include "minishell.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>

# define NO_FILES "No such file or directory"
# define MINI "minishell: "
# define IS_DIR "is a directory"

enum		e_builtin
{
	b_not_builtin,
	b_cd,
	b_echo,
	b_env,
	b_exit,
	b_pwd,
	b_unset,
	b_export
};

#endif