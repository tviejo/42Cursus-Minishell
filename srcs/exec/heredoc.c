/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:50 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/10 10:01:43 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_incorrect_delimiter_error(char *limiter, int nb_line)
{
	ft_dprintf(2, CORANGE "%swarning: here-document at line %d " RESET, MINI,
		nb_line);
	ft_dprintf(2, CORANGE "delimited by end-of-file (wanted '%s')\n" RESET,
		limiter);
}

static struct s_here_doc	open_here_document(void)
{
	t_here_doc	here_doc;
	char		*number;
	static int	nb = 0;

	number = ft_itoa(nb);
	here_doc.name = ft_strjoin("/tmp/here-document-", number);
	here_doc.fd = open(here_doc.name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(number);
	while (here_doc.fd < 0)
	{
		nb++;
		number = ft_itoa(nb);
		free(here_doc.name);
		here_doc.name = ft_strjoin("/tmp/here-document-", number);
		here_doc.fd = open(here_doc.name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		free(number);
	}
	return (here_doc);
}

static bool	find_limiter(char *str, char *limiter)
{
	int	i;

	i = 0;
	while (str[i] != '\0' || limiter[i] != '\0')
	{
		if (str[i] != limiter[i])
			return (false);
		i++;
	}
	if (str[i] == '\0' && limiter[i] == '\0')
		return (true);
	return (false);
}

static void	get_line(t_here_doc here_doc, char *limiter)
{
	char	*output;
	int		nb_line;

	nb_line = 1;
	signal_here_doc();
	while (1)
	{
		output = readline("> ");
		if (output == NULL || find_limiter(output, limiter) == true
			|| g_signal != 0)
			break ;
		write(here_doc.fd, output, ft_strlen(output));
		write(here_doc.fd, "\n", 1);
		free(output);
		nb_line++;
	}
	if (output == NULL && g_signal == 0)
		print_incorrect_delimiter_error(limiter, nb_line);
	free(output);
	close(here_doc.fd);
}

char	*create_here_doc(char *limiter)
{
	t_here_doc	here_doc;

	here_doc = open_here_document();
	get_line(here_doc, limiter);
	return (here_doc.name);
}
/*
int	main(void)
{
	char	*limiter;
	char	*file_name;
	int		fd;
	char	*str;

	limiter = "LIMITER";
	file_name = create_here_doc(limiter);
	printf("file_name: %s\n", file_name);
	fd = open(file_name, O_RDONLY);
	str = get_next_line(fd);
	while ( str != NULL)
	{
		printf("line: %s\n", str);
		str = get_next_line(fd);
	}
	close(fd);
	free(file_name);
	return (0);
}
*/