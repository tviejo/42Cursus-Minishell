/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 05:00:55 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/30 16:46:21 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exit(2);
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

void	lex_and_parse(t_data *ms, char *cmdline)
{
	char	*lexcmdline;

	lexcmdline = lexer(ms, cmdline);
	if (ms->debug_mode > 0)
		ft_printf("  lexcmdline: %s\n", lexcmdline);
	parse_cmdline(ms, lexcmdline);
	free(lexcmdline);
	if (ms->debug_mode > 0)
		print_cmdtree(ms);
}

void	execute(t_data *mshell)
{
	if (mshell->cmdtree == NULL || mshell->cmdtree->nb_command == 0)
		return ;
	init_exec(mshell);
	exec_cmdtree(mshell->cmdtree, mshell);
	close_exec(mshell);
}

int	main(int argc, char **argv, char **env)
{
	char	*cmdline;
	t_data	mshell;

	init(&mshell, argc, argv, env);
	while (true)
	{
		if (g_signal != 0)
			mshell.error_code = g_signal;
		signal_init();
		cmdline = read_prompt();
		if (cmdline == NULL)
		{
			mshell.error_code = 131;
			break ;
		}
		add_history(cmdline);
		lex_and_parse(&mshell, cmdline);
		free(cmdline);
		execute(&mshell);
		free_cmdtree(&mshell);
	}
	ft_printf("exit\n");
	return (free_env(&mshell), free_parsing(&mshell), mshell.error_code);
}
