/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:36:00 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/29 01:36:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*new_ary;
	int		i;
	int		check;
	char	buf;
	t_list	*lst;
	t_list	*curr;

	i = 0;
	lst = NULL;
	buf = '\0';
	while (buf != '\n')
	{
		check = read(fd, &buf, 1);
		if (check != 0)
		{
			curr = ft_lstnew(&buf);
			ft_lstadd_back(&lst, curr);
		}
		else
			return (NULL);
	}
	curr = lst;
	new_ary = (char *)malloc(sizeof(char) * (ft_lstsize(curr) + 1));
	if (new_ary == NULL)
		return (NULL);
	curr = lst;
	while (curr)
	{
		new_ary[i] = *((char *)((curr)->content));
		curr = (curr)->next;
		i++;
	}
	new_ary[i] = '\0';
	ft_lstclear(&lst, free);
	return (new_ary);
}

int main()
{
	int fd;
	int	i;
	char	*str;

	i = 0;
	str = "123";
	fd = open("a.txt", O_RDONLY);

	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		printf("%s", str);
		i++;
	}
	free(str);
}