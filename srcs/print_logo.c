/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:47:13 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/09 21:57:07 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_minishell(void)
{
	ft_dprintf(2, CBLUE CBOLD);
	ft_dprintf(2, "    __  ________   ___________ __  __________    __ \n");
	ft_dprintf(2, "   /  |/  /  _/ | / /  _/ ___// / / / ____/ /   / / \n");
	ft_dprintf(2, "  / /|_/ // //  |/ // / |__ |/ /_/ / __/ / /   / /  \n");
	ft_dprintf(2, " / /  / // // /|  // / ___/ / __  / /___/ /___/ /___\n");
	ft_dprintf(2, "/_/  /_/___/_/ |_/___//____/_/ /_/_____/_____/_____/\n\n");
	ft_dprintf(2, "Thomas Viejo & Aurélien de Sarrau (juillet-aout 2024)\n\n");
	ft_dprintf(2, RESET);
	return (0);
}

char *create_prompt(t_data *mshell)
{
	char *prompt;
	char *prompt2;
	char buffer[4096];

	getcwd(buffer, 4096);
	prompt2 = ft_strjoin(CBLUE CBOLD, buffer);
	prompt = ft_strjoin(prompt2, RESET);
	free(prompt2);
	if (mshell->error_code != 0)
		prompt2 = ft_strjoin(prompt, CRED CBOLD);
	else
		prompt2 = ft_strjoin(prompt, CGREEN CBOLD);
	free(prompt);
	prompt = ft_strjoin(prompt2, "  minishell> ");
	free(prompt2);
	prompt2 = ft_strjoin(prompt, RESET);
	free(prompt);
	return (prompt2);
}
