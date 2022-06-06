/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:51:28 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/06 19:22:42 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_with_s1(char **s1, char *new_str, int *index, int flag)
{
	int	cnt;

	cnt = 0;
	while ((*s1)[cnt])
	{
		new_str[(*index)++] = (*s1)[cnt];
		cnt++;
	}
	if (flag == 1)
		new_str[(*index)++] = ' ';
	return (new_str);
}

static char	*fill_with_s2(char *s2, char *new_str, int *index)
{
	int	cnt;

	cnt = 0;
	while (s2[cnt])
	{
		new_str[(*index)++] = s2[cnt];
		cnt++;
	}
	return (new_str);
}

char	*ft_strjoin_free(char **s1, char *s2, int flag)
{
	char	*new_str;
	int		index;
	int		s1_len;
	int		s2_len;

	index = 0;
	s1_len = ft_strlen(*s1);
	s2_len = ft_strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!new_str)
	{
		free(*s1);
		return (NULL);
	}
	if (s1_len != 0)
		new_str = fill_with_s1(s1, new_str, &index, flag);
	if (s2_len != 0)
		new_str = fill_with_s2(s2, new_str, &index);
	new_str[index] = '\0';
	if (*s1 != NULL)
		free(*s1);
	return (new_str);
}
