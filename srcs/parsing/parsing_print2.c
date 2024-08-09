/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 08:16:59 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/09 09:59:18 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_debug_print_npi_stack(t_data *p)
{
	if (p->debug_mode > 0)
	{
		ft_dprintf(p->pile_npi->print_fd, " ");
		stack_print(p->pile_npi, false,
			(t_print_elem_fct)print_stack_node, p);
	}
}

void	print_stack_node(t_cmdtree *cmdtree, t_data *ms)
{
	if (cmdtree->type > nt_piped_cmd)
		ft_dprintf(ms->debug_fd, "[%s]", ms->operators[cmdtree->type].token);
	else
		ft_dprintf(ms->debug_fd, "[%s]", cmdtree->argument[0]);
}

void	print_char_xtimes(int fd, char c, int times)
{
	while (times-- > 0)
		ft_dprintf(fd, "%c", c);
}

void	print_str_xtimes(int fd, char *s, int times)
{
	while (times-- > 0)
		ft_dprintf(fd, "%s", s);
}
