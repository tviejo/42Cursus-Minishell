/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:49:51 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/06/04 00:58:43 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* GNL with doubly linked list */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <unistd.h>

typedef struct s_gnl_buflst	t_gnl_buflst;

struct s_gnl_buflst
{
	t_gnl_buflst	*next;
	t_gnl_buflst	*pred;
	int				fd;
	char			*bufnextline;
	char			buffer[BUFFER_SIZE + 1];
};

//size_t	ft_strlen(const char *str);
//size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin_ex2(char const *s1, char const *s2, char const *s2endptr);
//char	*ft_strchr(const char *s, int c);

void	gnlbuf_release(t_gnl_buflst **plist, t_gnl_buflst *node);
void	gnlbuf_release_by_fd(t_gnl_buflst **plist, int fd);
char	*get_next_line(int fd);

#endif