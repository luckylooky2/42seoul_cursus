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

static	t_list	*ft_make_linked_list(int fd, t_list	*lst, char *buf)
{
	int		check;
	char	*new_char;
	t_list	*new_node;

	while (*buf != '\n')
	{
		check = read(fd, buf, 1);
		if (check != 0)
		{
			new_char = (char *)malloc(sizeof(char));
			*new_char = *buf;
			new_node = ft_lstnew(new_char);
			if (new_char == NULL || new_node == NULL)
			{
				ft_lstclear(&lst, free);
				return (NULL);
			}
			ft_lstadd_back(&lst, new_node);
		}
		else
			return (lst);
	}
	return (lst);
}

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE];
	char	*new_str;
	int		i;
	t_list	*lst;
	t_list	*curr;

	i = 0;
	*buf = '\0';
	lst = NULL;
	lst = ft_make_linked_list(fd, lst, buf);
	if (lst == NULL)
		return (NULL);
	curr = lst;
	new_str = (char *)malloc(sizeof(char) * (ft_lstsize(curr) + 1));
	if (new_str == NULL)
		return (NULL);
	while (curr)
	{
		new_str[i++] = *((char *)((curr)->content));
		curr = (curr)->next;
	}
	new_str[i] = '\0';
	ft_lstclear(&lst, free);
	return (new_str);
}

/*
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
		free(str);
		i++;
	}
}
*/