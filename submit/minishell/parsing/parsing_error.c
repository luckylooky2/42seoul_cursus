/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:42:47 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/24 16:58:57 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	get_token_type(char c)
{
	if (c == '>' || c == '<' || c == ';' || c == '&' || c == '|' || c == ' ' || \
	c == '(' || c == ')')
		return (c);
	return (0);
}

static char	*get_including_token(char *input, int i)
{
	int	start;
	int	end;

	start = i;
	while (0 < start && get_token_type(input[start - 1]) == get_token_type(\
	input[start]))
		start--;
	end = i + 1;
	while (input[end] && get_token_type(input[end - 1]) == get_token_type(\
	input[end]))
		end++;
	if (get_token_type(input[start]) && 2 < end - start)
		end = start + 2;
	return (ft_substr(input, start, end - start));
}

static char	*get_next_token(char *input, int i)
{
	while (input[i] && input[i] == ' ')
		i++;
	if (!input[i])
		return (ft_strdup("newline"));
	return (get_including_token(input, i));
}

static char	*get_token(char *input, int i)
{
	if (!input[i])
		return (ft_strdup("newline"));
	else if (input[i] == ' ')
		return (get_next_token(input, i));
	else
		return (get_including_token(input, i));
}

void	parsing_error(char *input, char *token, int i)
{
	char	*message;
	char	*message_with_suffix;
	char	free_flag;

	free_flag = 0;
	if (token == NULL)
	{
		token = get_token(input, i);
		free_flag = 1;
	}
	message = ft_strjoin("syntax error near unexpected token `", token);
	message_with_suffix = ft_strjoin(message, "'");
	error_handle(message_with_suffix);
	free(message);
	free(message_with_suffix);
	if (free_flag)
		free(token);
}
