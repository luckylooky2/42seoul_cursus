/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:10:02 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/21 14:13:09 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	return ;
}

static char	*ft_copy(char const *str2, char const *str1, char *ptr_ary)
{
	int	i;

	i = 0;
	while (*str2 != *str1)
	{
		ptr_ary[i] = *str1;
		i++;
		str1++;
	}
	ptr_ary[i] = '\0';
	return ((char *)str1);
}

static char	*ft_second_malloc(char const *str2, char c, char **str, int i)
{
	char const	*str1;

	str1 = str2;
	while (*str2)
	{
		if (*str2 == c || *(str2 + 1) == '\0')
		{
			if (*str2 != c && *(str2 + 1) == '\0')
				str2++;
			if (*str2 != *str1)
			{
				str[i] = (char *)malloc(sizeof(char) * (str2 - str1 + 1));
				if (str[i] == NULL)
					return (str[i]);
				str1 = (char const *)ft_copy(str2, str1, str[i]);
				i++;
			}
			str1++;
		}
		if (*str2 != '\0')
			str2++;
	}
	if (i == 0)
		return (str[i]);
	return (str[i - 1]);
}

static int	ft_len_first_malloc(char const *s, char c)
{
	char const	*front;
	char const	*back;
	int			i;
	int			cnt;
	int			len;

	i = 0;
	cnt = 0;
	len = ft_strlen((char *)s);
	front = s;
	back = (s + 1);
	while (i++ < len)
	{
		if (*front != c && (*back == c || *back == '\0'))
			cnt++;
		front++;
		back++;
	}
	return (cnt);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	char	*last_str;
	int		i;
	int		len;

	i = 0;
	len = ft_len_first_malloc(s, c);
	str = (char **)malloc((len + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	if (len == 0)
		return (str);
	last_str = ft_second_malloc(s, c, str, i);
	if (last_str == NULL)
	{
		ft_free(str);
		free(str);
		return (NULL);
	}
	return (str);
}
