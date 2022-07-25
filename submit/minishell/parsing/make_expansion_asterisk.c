/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_expansion_asterisk.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:36:32 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/22 19:08:28 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	append_to_syntax(t_syntax *s, char *str)
{
	size_t	len;
	char	*new_input;
	char	*new_meaning;

	if (str == NULL)
		panic_memory();
	len = ft_strlen(s->input) + ft_strlen(str) + 1;
	new_input = malloc((len + 1) * sizeof(char));
	if (new_input == NULL)
		panic_memory();
	new_meaning = malloc(len * sizeof(char));
	if (new_meaning == NULL)
		panic_memory();
	ft_strlcpy(new_input, s->input, ft_strlen(s->input) + 1);
	ft_memcpy(new_meaning, s->meaning, ft_strlen(s->input));
	ft_strlcat(new_input + ft_strlen(s->input), " ", 2);
	new_meaning[ft_strlen(s->input)] = 1;
	ft_strlcat(new_input + ft_strlen(s->input) + 1, str, ft_strlen(str) + 1);
	ft_memset(new_meaning + ft_strlen(s->input) + 1, 0, ft_strlen(str));
	free(str);
	free(s->input);
	free(s->meaning);
	s->input = new_input;
	s->meaning = new_meaning;
}

static int	does_match(char *name_buffer, int name_length, char *regex)
{
	char	*name_str;
	int		result;

	if (1 <= name_length && name_buffer[0] == '.')
		return (0);
	name_str = ft_substr(name_buffer, 0, name_length);
	if (name_str == NULL)
		panic_memory();
	result = regex_matcher(name_str, regex);
	free(name_str);
	return (result);
}

static t_syntax	*make_syntax_matching_regex(char *regex)
{
	t_syntax	*s;
	t_dirent	*dir;

	if (get_next_dir(INIT_DIR) == NULL)
		return (NULL);
	s = malloc(sizeof(t_syntax));
	if (s == NULL)
		panic_memory();
	s->input = ft_strdup("");
	s->meaning = ft_strdup("");
	if (s->input == NULL || s->meaning == NULL)
		panic_memory();
	while (1)
	{
		dir = get_next_dir(GET_DIR);
		if (dir == NULL)
			break ;
		if (does_match(dir->d_name, dir->d_namlen, regex))
			append_to_syntax(s, ft_substr(dir->d_name, 0, dir->d_namlen));
	}
	get_next_dir(CLOSE_DIR);
	return (s);
}

static int	fetch_and_replace(t_syntax *s, int i, char *regex, char *start)
{
	t_syntax	*result_syntax;
	int			retval;

	result_syntax = make_syntax_matching_regex(regex);
	if (result_syntax != NULL && *result_syntax->input)
	{
		retval = ft_strlen(start + ft_strlen(regex));
		ft_memmove(start, start + ft_strlen(regex), retval + 1);
		ft_memmove(s->meaning + (start - s->input), \
		s->meaning + (start - s->input) + ft_strlen(regex), retval);
		retval = start + ft_strlen(result_syntax->input) - (s->input + i);
		insert_syntax(s, result_syntax, start - s->input);
		delete_t_syntax(result_syntax);
		return (retval);
	}
	if (result_syntax != NULL)
		delete_t_syntax(result_syntax);
	return (1);
}

void	expand_asterisk(t_syntax *s, int i)
{
	char	*start;
	char	*end;
	char	*regex;

	while (s->input[i])
	{
		if (s->input[i] == '*' && s->meaning[i] == 1)
		{
			start = s->input + i;
			while (s->input < start && *(start - 1) != ' ' && \
			s->meaning[start - s->input - 1] == 1)
				start--;
			end = s->input + i + 1;
			while (*end && *end != ' ' && s->meaning[end - s->input] == 1)
				end++;
			regex = ft_substr(start, 0, end - start);
			if (regex == NULL)
				panic_memory();
			i += fetch_and_replace(s, i, regex, start);
			free(regex);
			expand_asterisk(s, i);
			return ;
		}
		i++;
	}
}
