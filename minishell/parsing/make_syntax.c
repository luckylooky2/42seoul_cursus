/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 16:24:57 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/20 20:48:27 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	insert_syntax(t_syntax *s1, t_syntax *s2, int i)
{
	size_t	len;
	char	*new_input;
	char	*new_meaning;

	len = ft_strlen(s1->input) + ft_strlen(s2->input);
	new_input = malloc((len + 1) * sizeof(char));
	new_meaning = malloc(len * sizeof(char));
	if (new_input == NULL || new_meaning == NULL)
		panic_memory();
	ft_strlcpy(new_input, s1->input, i + 1);
	ft_strlcat(new_input, s2->input, i + ft_strlen(s2->input) + 1);
	ft_strlcat(new_input, s1->input + i, len + 1);
	ft_memcpy(new_meaning, s1->meaning, i);
	ft_memcpy(new_meaning + i, s2->meaning, ft_strlen(s2->input));
	ft_memcpy(new_meaning + i + ft_strlen(s2->input), s1->meaning + i, \
	ft_strlen(s1->input + i));
	free(s1->input);
	free(s1->meaning);
	s1->input = new_input;
	s1->meaning = new_meaning;
}

static int	there_are_only_space(char *input, int len)
{
	while (len-- && *input == ' ')
		input++;
	return (len == -1 || *input == 0);
}

static int	check_before_slice(t_syntax *s, int i, int length, t_delimiter d)
{
	if (d == SEMICOLON)
	{
		if (i == 0)
			return (0);
		return (length == 0 && i < (int)ft_strlen(s->input));
	}
	return (length == 0 || (there_are_only_space(s->input + i, length) && \
	length != (int)ft_strlen(s->input)));
}

t_syntax	*slice_syntax(t_syntax *s, int i, int length, t_delimiter delim)
{
	t_syntax	*syntax;

	if (check_before_slice(s, i, length, delim))
	{
		if (global_status(GET_P_ERROR, 0) == 0)
			global_status(SET_P_ERROR, delim);
		return (NULL);
	}
	if (length == 0)
		return (NULL);
	syntax = malloc(sizeof(t_syntax));
	if (syntax == NULL)
		panic_memory();
	syntax->input = malloc((length + 1) * sizeof(char));
	if (syntax->input == NULL)
		panic_memory();
	syntax->meaning = malloc(length * sizeof(char));
	if (syntax->meaning == NULL)
		panic_memory();
	ft_strlcpy(syntax->input, s->input + i, length + 1);
	ft_memcpy(syntax->meaning, s->meaning + i, length);
	return (syntax);
}

t_syntax	*syntax_from_input(char *input, char *meaning)
{
	t_syntax	*syntax;

	if (meaning == NULL)
		return (NULL);
	syntax = malloc(sizeof(t_syntax));
	if (syntax == NULL)
		panic_memory();
	syntax->input = ft_strdup(input);
	syntax->meaning = meaning;
	return (syntax);
}
