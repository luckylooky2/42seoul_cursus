/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:57:56 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:59:11 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static int	heredoc(char *filename, char *delimiter)
{
	char	*input;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		error_errno(filename);
		return (-1);
	}
	while (global_status(GET_INTERACTIVE, 0) == HEREDOC)
	{
		input = readline("> ");
		if (input == NULL || \
		(!ft_strncmp(input, delimiter, ft_strlen(delimiter)) && \
		ft_strlen(delimiter) == ft_strlen(input)))
		{
			free(input);
			break ;
		}
		ft_putendl_fd(input, fd);
		free(input);
	}
	close(fd);
	control_in_and_out(RESTORE_STDIO);
	return (0);
}

char	*heredoc_manager(t_heredoc_cmd cmd, char *delimiter)
{
	static char		*path = "./heredoc-temp-";
	static t_deq	*files = NULL;
	static int		id = 0;

	if (files == NULL)
	{
		files = ft_deq_new();
		if (files == NULL)
			panic_memory();
		id = 0;
	}
	if (cmd == CLOSE_HEREDOC)
		ft_deq_delete(&files, delete_temp_file);
	else if (cmd == PUT_HEREDOC)
	{
		control_in_and_out(BACKUP_STDIO);
		if (ft_deq_push_back(files, make_temp_file_name(path, id++)) == -1)
			panic_memory();
		if (heredoc(files->tail->prev->data, delimiter) == -1)
			return (NULL);
		return (files->tail->prev->data);
	}
	return (0);
}

static void	do_heredoc(t_syntax *s, int i, int j, int len)
{
	int			l;
	char		*filename;
	char		*delimiter;
	t_syntax	*new_syntax;

	ft_memmove(s->input + i, s->input + j, ft_strlen(s->input + j) + 1);
	ft_memmove(s->meaning + i, s->meaning + j, ft_strlen(s->input + j));
	delimiter = ft_substr(s->input, i, len);
	if (delimiter == NULL)
		panic_memory();
	l = ft_strlen(s->input + i + len) + 1;
	ft_memmove(s->input + i, s->input + i + len, l);
	ft_memmove(s->meaning + i, s->meaning + i + len, l - 1);
	filename = heredoc_manager(PUT_HEREDOC, delimiter);
	free(delimiter);
	if (filename == NULL)
		return ;
	new_syntax = syntax_from_input(filename, make_meaning(filename));
	if (new_syntax == NULL)
		return ;
	insert_syntax(s, new_syntax, i);
	delete_t_syntax(new_syntax);
}

static void	replace_heredoc(t_syntax *s, int i)
{
	int		first;
	int		start;
	int		len;

	first = i - 1;
	while (s->input[i] == ' ')
		i++;
	start = i;
	while (s->input[i])
	{
		if (1 <= s->meaning[i] && \
		(s->input[i] == '\"' || s->input[i] == '\'' || s->input[i] == '\\'))
		{
			len = ft_strlen(s->input + i);
			ft_memmove(s->input + i, s->input + i + 1, len);
			ft_memmove(s->meaning + i, s->meaning + i + 1, len - 1);
			continue ;
		}
		else if (1 <= s->meaning[i] && (s->input[i] == ' ' || \
		s->input[i] == '&' || s->input[i] == '|' || s->input[i] == ';' || \
		s->input[i] == ')'))
			break ;
		i++;
	}
	do_heredoc(s, first, start, i - start);
}

void	process_heredoc(t_syntax *syntax)
{
	int			i;
	int			j;
	int			len;
	t_syntax	*subshell_syntax;

	i = -1;
	while (syntax->input[++i] && global_status(GET_INTERACTIVE, 0) == HEREDOC)
	{
		if (!ft_strncmp("<<", syntax->input + i, 2) && syntax->meaning[i])
			replace_heredoc(syntax, i + 2);
		else if (syntax->input[i] == '(' && syntax->meaning[i] == 1)
		{
			j = i++ + 1;
			while (syntax->input[j] != ')' || syntax->meaning[j] != 1)
				j++;
			subshell_syntax = slice_syntax(syntax, i, j - i, NO_DELIM);
			process_heredoc(subshell_syntax);
			len = ft_strlen(syntax->input + j);
			ft_memmove(syntax->input + i, syntax->input + j, len + 1);
			ft_memmove(syntax->meaning + i, syntax->meaning + j, len);
			insert_syntax(syntax, subshell_syntax, i);
			delete_t_syntax(subshell_syntax);
		}
	}
}
