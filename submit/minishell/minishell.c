/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:53:15 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/24 17:27:53 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_deq	*parse_args(char *input)
{
	t_syntax	*syntax;
	t_deq		*broken_semicolon;

	syntax = syntax_from_input(input, make_meaning(input));
	if (syntax == NULL || parsing_error_on_syntax(syntax))
	{
		delete_t_syntax(syntax);
		return (NULL);
	}
	broken_semicolon = break_semicolon(syntax);
	break_linker(broken_semicolon);
	break_pipe(broken_semicolon);
	delete_t_syntax(syntax);
	if (global_status(GET_P_ERROR, 0) == PRINTED)
	{
		ft_deq_delete(&broken_semicolon, delete_linked_commands);
		return (NULL);
	}
	process_heredoc(broken_semicolon);
	return (broken_semicolon);
}

static void	do_command(t_deq *linked_commands)
{
	t_gnode		*cur;
	t_commands	*commands;
	int			exit_status;

	cur = linked_commands->tail->next;
	while (cur != linked_commands->tail)
	{
		commands = cur->data;
		exit_status = global_status(GET_STATUS, 0);
		if ((commands->prev == AND && exit_status == 0) || \
		(commands->prev == OR && exit_status != 0) || commands->prev == NONE)
		{
			do_exec(make_expansions(commands->piped_commands));
		}
		cur = cur->next;
	}
}

static void	do_commands(t_deq *broken_semicolon)
{
	t_gnode	*semicolon_unit;

	semicolon_unit = broken_semicolon->tail->next;
	while (semicolon_unit != broken_semicolon->tail)
	{
		do_command(semicolon_unit->data);
		semicolon_unit = semicolon_unit->next;
	}
	ft_deq_delete(&broken_semicolon, delete_linked_commands);
}

static int	routine(char *input)
{
	t_deq	*parsed_args;
	char	free_flag;

	free_flag = 0;
	if (input == NULL)
	{
		input = readline("\033[0m$ ");
		if (input == NULL)
			return (0);
		free_flag = 1;
		add_history(input);
	}
	global_status(SET_P_ERROR, 0);
	parsed_args = parse_args(input);
	global_status(SET_INTERACTIVE, 0);
	if (parsed_args != NULL)
		do_commands(parsed_args);
	else
		global_status(SET_STATUS, 258);
	global_status(SET_INTERACTIVE, 1);
	if (free_flag)
		free(input);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	env_commands(PUT_ENV, envp);
	if (argc != 1)
	{
		routine(argv[1]);
		env_commands(CLOSE_ENV, NULL);
		heredoc_manager(CLOSE_HEREDOC, NULL);
		exit(global_status(GET_STATUS, 0));
	}
	while (routine(NULL))
		;
	printf("exit\n");
	env_commands(CLOSE_ENV, NULL);
	heredoc_manager(CLOSE_HEREDOC, NULL);
	system("leaks minishell");
	return (0);
}
