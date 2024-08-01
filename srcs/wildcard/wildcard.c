/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:52:21 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/01 13:01:17 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
*/

bool	is_match(char *wcard, char *str)
{
	if (*wcard == '\0' && *str == '\0')
		return (true);
	if (*wcard == '*')
		return (is_match(wcard + 1, str) || (*str && is_match(wcard, str + 1)));
	if (*wcard == '?' || *wcard == *str)
		return (is_match(wcard + 1, str + 1));
	return (false);
}

static char	*read_directory(DIR *dir, char *wildcard)
{
	struct dirent	*names;
	char			*return_str;

	return_str = NULL;
	names = readdir(dir);
	while (names != NULL)
	{
		if (is_match(wildcard, names->d_name))
		{
			return_str = join_with_space(return_str, names->d_name);
		}
		names = readdir(dir);
	}
	return (return_str);
}

char	*find_wildcard(char *wildcard)
{
	DIR		*dir;
	char	*return_str;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("minishell: Error: Unable to open directory");
		return (NULL);
	}
	return_str = read_directory(dir, wildcard);
	if (closedir(dir) == -1)
	{
		perror("minishell: Error: Unable to close directory");
		return (NULL);
	}
	return (return_str);
}

/*
int	main(int argc, char **argv)
{
	char	*wildcard;
	char	*return_str;

	if (argc != 2)
	{
		printf("Usage: %s <wildcard>\n", argv[0]);
		return (1);
	}
	wildcard = argv[1];
	return_str = find_wildcard(wildcard);
	if (return_str == NULL)
		return (1);
	printf("%s\n", return_str);
	free(return_str);
	return (0);
}
*/