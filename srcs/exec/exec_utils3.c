/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:53:25 by tviejo            #+#    #+#             */
/*   Updated: 2024/08/06 17:41:15 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_exec(t_data *mshell)
{
	mshell->proccess = NULL;
	mshell->end_exec = false;
	mshell->oldtype = 0;
	mshell->side = e_left;
	calloc_pid(mshell, mshell->cmdtree);
	mshell->dupstdin = dup(STDIN_FILENO);
	mshell->dupstdout = dup(STDOUT_FILENO);
	mshell->subshell = false;
	mshell->redirected_infile = false;
	mshell->redirected_outfile = false;
	mshell->subshell_infile = NULL;
	mshell->subshell_outfile = NULL;
	mshell->end = false;
}

void	close_exec(t_data *mshell)
{
	ft_lstclear_process(&mshell->proccess);
	free(mshell->proccess);
	dup2(mshell->dupstdin, STDIN_FILENO);
	dup2(mshell->dupstdout, STDOUT_FILENO);
	close(mshell->dupstdout);
	close(mshell->dupstdin);
	ft_free_pid(mshell);
}

t_proccess	*ft_lstnew_int(int pid_index)
{
	t_proccess	*node;

	node = (t_proccess *)malloc(sizeof(t_proccess));
	if (node == NULL)
		return (node);
	node->pid_index = pid_index;
	node->next = NULL;
	return (node);
}

t_proccess	*ft_lstlast_process(t_proccess *lst)
{
	int	i;

	if (lst != NULL)
	{
		i = 0;
		while (lst->next != NULL)
		{
			lst = lst->next;
			i++;
		}
	}
	return (lst);
}

void	ft_lstadd_back_proccess(t_proccess **lst, t_proccess *new)
{
	if (new != NULL)
	{
		if (*lst != NULL)
			ft_lstlast_process(*lst)->next = new;
		else
			*lst = new;
	}
}
