/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 05:00:55 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/09 23:17:03 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_data *mshell, int argc, char **argv, char **env)
{
	mshell->error_fd = STDERR_FILENO;
	mshell->debug_fd = STDERR_FILENO;
	mshell->info_fd = STDERR_FILENO;
	mshell->error_code = 0;
	if (argc > 1)
		mshell->debug_mode = atoi(argv[1]);
	else
		mshell->debug_mode = 0;
	if (!init_parsing(mshell))
	{
		ft_putstr_fd("minishell [init_parsing]: error: malloc failed.\n",
			mshell->error_fd);
		exit(2);
	}
	store_env(mshell, env);
	rl_bind_key('\t', rl_complete);
	using_history();
	print_minishell();
}

char	*read_prompt(t_data *mshell)
{
	char	*cmdline;
	char	*prompt;

	prompt = create_prompt(mshell);
	cmdline = readline(prompt);
	while (cmdline != NULL && (cmdline[0] == '\0' || cmdline[0] == '\n'))
	{
		free(cmdline);
		cmdline = readline(prompt);
	}
	free(prompt);
	return (cmdline);
}

void	lex_and_parse(t_data *ms, char *cmdline)
{
	lexer(ms, cmdline);
	parser(ms);
	purger_lexqueue(ms->file_lex);
	purger_npistack(ms->pile_npi);
}

void	execute(t_data *mshell)
{
	if (mshell->cmdtree == NULL)
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
		signal_init();
		cmdline = read_prompt(&mshell);
		if (cmdline == NULL)
		{
			mshell.error_code = 131;
			break ;
		}
		if (g_signal != 0)
			mshell.error_code = g_signal;
		add_history(cmdline);
		lex_and_parse(&mshell, cmdline);
		free(cmdline);
		execute(&mshell);
		free_cmdtree(&mshell);
	}
	ft_printf("exit\n");
	return (free_env(&mshell), free_parsing(&mshell), mshell.error_code);
}
