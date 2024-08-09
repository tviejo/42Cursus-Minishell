/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tviejo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:16:44 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/09 22:01:30 by tviejo           ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define NO_FILES "No such file or directory"
# define MINI "minishell: "
# define IS_DIR "is a directory"
# define NO_PERM "Permission denied"

# define CRED "\001\e[0;31m\002"
# define CGREEN "\001\e[0;32m\002"
# define CBLUE "\001\e[0;34m\002"
# define CYELLOW "\001\e[0;33m\002"
# define CMAGENTA "\001\e[0;35m\002"
# define CCYAN "\001\e[0;36m\002"
# define CBOLD "\001\e[1m\002"
# define CITALIC "\001\e[3m\002"
# define CORANGE "\001\e[38;5;208m\002"
# define RESET "\001\e[0m\002"

enum	e_builtin
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