/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 05:00:55 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/25 13:41:00 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_minishell(void)
{
	ft_printf("    __  ________   ___________ __  __________    __ \n");
	ft_printf("   /  |/  /  _/ | / /  _/ ___// / / / ____/ /   / / \n");
	ft_printf("  / /|_/ // //  |/ // / |__ |/ /_/ / __/ / /   / /  \n");
	ft_printf(" / /  / // // /|  // / ___/ / __  / /___/ /___/ /___\n");
	ft_printf("/_/  /_/___/_/ |_/___//____/_/ /_/_____/_____/_____/\n\n");
	return (0);
}

void	execute(t_data *mshell)
{
	mshell->end_exec = false;
	calloc_pid(mshell, mshell->cmdtree);
	mshell->oldtype = 0;
	mshell->side = e_left;
	mshell->dupstdin = dup(STDIN_FILENO);
	mshell->dupstdout = dup(STDOUT_FILENO);
	exec_cmdtree(mshell->cmdtree, mshell);
	dup2(mshell->dupstdin, STDIN_FILENO);
	dup2(mshell->dupstdout, STDOUT_FILENO);
	close(mshell->dupstdout);
	close(mshell->dupstdin);
	ft_free_pid(mshell);
}

void	init(t_data *mshell, int argc, char **argv, char **env)
{
	mshell->error_code = 0;
	if (argc > 1)
		mshell->debug_mode = atoi(argv[1]);
	else
		mshell->debug_mode = 0;
	if (!init_parsing(mshell))
	{
		ft_putstr_fd("minishell [init_parsing]: error: malloc failed.\n", 2);
		exit(-1);
	}
	store_env(mshell, env);
	rl_bind_key('\t', rl_complete);
	using_history();
	print_minishell();
}
char	*read_prompt(void)
{
	char	*cmdline;

	cmdline = readline("minishell> ");
	while (cmdline != NULL && (cmdline[0] == '\0' || cmdline[0] == '\n'))
		cmdline = readline("minishell> ");
	return (cmdline);
}
int	main(int argc, char **argv, char **env)
{
	char	*cmdline;
	t_data	mshell;

	init(&mshell, argc, argv, env);
	while (true)
	{
		signal_init();
		cmdline = read_prompt();
		if (cmdline == NULL)
			break ;
		add_history(cmdline);
		parse_cmdline(&mshell, cmdline);
		free(cmdline);
		if (mshell.debug_mode > 0)
			print_cmdtree(&mshell);
		execute(&mshell);
		free_cmdtree(&mshell);
	}
	return (ft_printf("exit\n"), free_env(&mshell), free_parsing(&mshell), 0);
}
