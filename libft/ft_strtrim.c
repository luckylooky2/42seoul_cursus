/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:13:27 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/18 15:12:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_check_front(char const *s1, char const *set)
{
	int	index;
	int	set_index;
	int	cnt;

	index = 0;
	while (s1[index])
	{
		cnt = 0;
		set_index = 0;
		while (set[set_index])
		{
			if (s1[index] != set[set_index])
				cnt++;
			set_index++;
		}
		if (cnt == set_index)
			return ((char *)s1 + index);
		else
			index++;
	}
	return ((char *)s1 + index);
}

static char	*ft_check_back(char const *s1, char const *set)
{
	int	index;
	int	set_index;
	int	cnt;

	index = ft_strlen((char *)s1) - 1;
	if (index == -1)
		return ((char *)s1);
	while (index >= 0)
	{
		cnt = 0;
		set_index = 0;
		while (set[set_index])
		{
			if (s1[index] != set[set_index])
				cnt++;
			set_index++;
		}
		if (cnt == set_index)
			return ((char *)s1 + index);
		else
			index--;
	}
	return ((char *)s1 + index);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1_front;
	char	*s1_back;
	char	*ptr;
	int		i;

	i = 0;
	s1_front = ft_check_front(s1, set);
	s1_back = ft_check_back(s1, set);
	if (s1_front > s1_back)
		s1_front = s1_back;
	ptr = (char *)malloc(sizeof(char) * (s1_back - s1_front + 2));
	if (!ptr)
		return (0);
	while (s1_front != s1_back)
	{
		ptr[i] = *(s1_front);
		i++;
		s1_front++;
	}
	ptr[i] = *(s1_front);
	if (i != 0)
		ptr[i + 1] = 0;
	return (ptr);
}

// #include <stdio.h>
// #include <string.h>
// #define TRIM_SET_PLACEHOLDER " \n\t"

// int main()
// {
// 	// char	*s1 = "   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !\n   \n \n \t\t\n  ";
// 	// char	*s2 = "Hello \t  Please\n Trim me !";
// 	// char	*ret = ft_strtrim(s1, TRIM_SET_PLACEHOLDER);

// 	// char	*s1 = "Hello \t  Please\n Trim me !";
// 	// char	*s2 = "Hello \t  Please\n Trim me !";

// 	// char	*ret = ft_strtrim(s1, TRIM_SET_PLACEHOLDER);

// 	// char	*s1 = "";
// 	// char	*s2 = "";

// 	// char	*ret = ft_strtrim(s1, TRIM_SET_PLACEHOLDER);

// 	// char	*s1 = "  \t \t \n   \n\n\n\t";
// 	// char	*s2 = "";
// 	// char	*ret = ft_strtrim(s1, TRIM_SET_PLACEHOLDER);
	
// 	// if (!strcmp(ret, s2))
// 	// 	printf("good");
// 	// else
// 	// 	printf("bad");

// 	// int size;
// 	// int r_size;

// 	char	*s1 = "\t   \n\n\n  \n\n\t    Hello \t  Please\n Trim me !\t\t\t\n  \t\t\t\t  ";
// 	char	*s2 = "Hello \t  Please\n Trim me !";

// 	printf("%s	\n", ft_strtrim(s1, TRIM_SET_PLACEHOLDER));
// 	printf("%s	\n", s2);
	
// 	// size = ft_strlen(ft_strtrim(s1, TRIM_SET_PLACEHOLDER));
// 	// r_size = ft_strlen(s2);
// 	// printf("%d %d", size, r_size);

// 	// if (size == r_size + 1)
// 	// 	printf("good");
// 	// else
// 	// 	printf("bad");
// }
