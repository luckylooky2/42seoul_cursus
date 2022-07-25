/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_expansion_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:36:32 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/22 20:44:34 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	save_meaning_of_space(char *meaning, char *str)
{
	while (*str)
	{
		if (*str == ' ')
			*meaning = 1;
		str++;
		meaning++;
	}
}

static void	do_replace(t_syntax *s, char *str, int i, char *end)
{
	int		len;
	char	*new_input;
	char	*new_meaning;

	len = ft_strlen(s->input) + ft_strlen(str) - (end - s->input - i);
	new_input = malloc((len + 1) * sizeof(char));
	new_meaning = malloc(len * sizeof(char));
	if (new_input == NULL || new_meaning == NULL)
		panic_memory();
	ft_strlcpy(new_input, s->input, i + 1);
	ft_strlcat(new_input, str, i + ft_strlen(str) + 1);
	ft_strlcat(new_input, end, i + ft_strlen(str) + ft_strlen(end) + 1);
	ft_memcpy(new_meaning, s->meaning, i);
	ft_memset(new_meaning + i, 0, ft_strlen(str));
	ft_memcpy(new_meaning + i + ft_strlen(str), s->meaning + (end - s->input), \
	ft_strlen(end));
	save_meaning_of_space(new_meaning + i, str);
	free(s->input);
	free(s->meaning);
	s->input = new_input;
	s->meaning = new_meaning;
}

static char	*fetch_env_wrapper(char **key)
{
	char	*value;

	value = env_commands(GET_ENV, key);
	if (value == NULL)
	{
		if (ft_strlen(*key) == 0)
			value = "$";
		else
			value = "";
	}
	return (ft_strdup(value));
}

static void	fetch_and_replace(t_syntax *s, int *i)
{
	char	*end;
	char	*key;
	char	*value;

	end = s->input + *i + 1;
	if (*end == '?')
	{
		key = ft_strdup("");
		value = ft_itoa(global_status(GET_STATUS, 0));
	}
	else
	{
		while (ft_isalnum(*end) || *end == '_')
			end++;
		key = ft_substr(s->input + *i, 1, --end - s->input - *i);
		if (key == NULL)
			panic_memory();
		value = fetch_env_wrapper(&key);
		if (value == NULL)
			panic_memory();
	}
	do_replace(s, value, *i, ++end);
	*i += (int)ft_strlen(value);
	free(key);
	free(value);
}

void	expand_env(t_syntax *s, int i)
{
	while (s->input[i])
	{
		if (s->input[i] == '$' && s->meaning[i] == 1)
		{
			fetch_and_replace(s, &i);
			expand_env(s, i);
			return ;
		}
		i++;
	}
	return ;
}
