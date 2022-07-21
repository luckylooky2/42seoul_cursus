/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:21:59 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/12 18:19:49 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_num_of_str(char const *s, char c);
static int		allocate_str(char **str_set, char const *s, char c);
static int		free_str(char **str_set);

char	**ft_split(char const *s, char c)
{
	char	**str_set;
	size_t	num_of_str;

	num_of_str = get_num_of_str(s, c);
	str_set = (char **)malloc(sizeof(char *) * (num_of_str + 1));
	if (str_set == 0)
		return (0);
	if (allocate_str(str_set, s, c) == 0)
		return (0);
	return (str_set);
}

static size_t	get_num_of_str(char const *s, char c)
{
	const char	*prev;
	const char	*next;
	size_t		num_of_str;

	prev = s;
	num_of_str = 0;
	while (*prev)
	{
		next = ft_strchr(prev, c);
		if (next != prev)
			++num_of_str;
		if (next == 0 || *next == 0)
			break ;
		prev = ++next;
	}
	return (num_of_str);
}

static int	allocate_str(char **str_set, char const *s, char c)
{
	const char	*prev;
	const char	*next;
	char		*temp;

	prev = s;
	while (*prev)
	{
		next = ft_strchr(prev, c);
		if (next != prev)
		{
			if (next == 0 || *next == 0)
				temp = ft_strdup(prev);
			else
				temp = ft_substr(prev, 0, next - prev);
			if (temp == 0)
				return (free_str(str_set));
			*str_set++ = temp;
		}
		if (next == 0 || *next == 0)
			break ;
		prev = ++next;
	}
	*str_set = 0;
	return (1);
}

static int	free_str(char **str_set)
{
	char	**to_free;

	to_free = str_set;
	while (*str_set)
	{
		free(*str_set);
		++str_set;
	}
	free(to_free);
	return (0);
}
