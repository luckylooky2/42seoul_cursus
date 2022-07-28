/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:42:47 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:57:51 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

static char	get_token_type(char c, char m)
{
	if (m == 0)
		return (0);
	if (c == '>' || c == '<' || c == ';' || c == '&' || c == '|' || c == ' ' || \
	c == '(' || c == ')')
		return (c);
	return (0);
}

static char	*get_including_token(t_syntax *s, int i)
{
	int	start;
	int	end;

	start = i;
	while (0 < start && get_token_type(s->input[start - 1], s->meaning[start \
	- 1]) == get_token_type(s->input[start], s->meaning[start]))
		start--;
	end = i + 1;
	while (s->input[end] && get_token_type(s->input[end - 1], s->meaning[end \
	- 1]) == get_token_type(s->input[end], s->meaning[end]))
		end++;
	if (get_token_type(s->input[start], s->meaning[start]) && 2 < end - start)
		end = start + 2;
	return (ft_substr(s->input, start, end - start));
}

static char	*get_next_token(t_syntax *syntax, int i)
{
	while (syntax->input[i] && syntax->input[i] == ' ')
		i++;
	if (!syntax->input[i])
		return (ft_strdup("newline"));
	return (get_including_token(syntax, i));
}

static char	*get_token(t_syntax *syntax, int i)
{
	if (!syntax->input[i])
		return (ft_strdup("newline"));
	else if (syntax->input[i] == ' ')
		return (get_next_token(syntax, i));
	else
		return (get_including_token(syntax, i));
}

void	parsing_error(t_syntax *syntax, char *token, int i)
{
	char	*message;
	char	free_flag;

	free_flag = 0;
	if (token == NULL)
	{
		token = get_token(syntax, i);
		free_flag = 1;
	}
	message = make_message("syntax error near unexpected token `", token, "'");
	error_handle(message);
	free(message);
	if (free_flag)
		free(token);
}
