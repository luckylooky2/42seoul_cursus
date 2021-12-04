/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:36:00 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/02 15:25:20 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*ft_make_linked_list(t_list *char_lst, char *buf)
{
	char	*new_char;
	t_list	*new_node;

	new_char = (char *)malloc(sizeof(char));
	if (new_char == NULL)
	{
		ft_lstclear(&char_lst, free);
		return (NULL);
	}
	*new_char = *buf;
	new_node = ft_lstnew(new_char);
	if (new_node == NULL)
	{
		ft_lstclear(&char_lst, free);
		return (NULL);
	}
	ft_lstadd_back(&char_lst, new_node);
	return (char_lst);
}

static	t_list	*ft_read_n_check_file(int fd, t_list *char_lst, char *buf)
{
	int	check;

	*buf = '\0';
	while (*buf != '\n')
	{
		check = read(fd, buf, 1);
		if (check == 1)
		{
			char_lst = ft_make_linked_list(char_lst, buf);
			if (char_lst == NULL)
				return (NULL);
		}
		else if (check == 0)
			return (char_lst);
		else if (check == -1)
		{
			ft_lstclear(&char_lst, free);
			return (NULL);
		}
	}
	return (char_lst);
}

static char	*ft_copy_str(char *new_str, t_list *char_lst)
{
	int		i;
	t_list	*curr;

	i = 0;
	curr = char_lst;
	while (curr)
	{
		new_str[i] = *((char *)((curr)->content));
		curr = (curr)->next;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE];
	char	*new_str;
	t_list	*char_lst;
	t_list	*curr;

	char_lst = NULL;
	if (fd < 0)
		return (NULL);
	char_lst = ft_read_n_check_file(fd, char_lst, buf);
	if (char_lst == NULL)
		return (NULL);
	curr = char_lst;
	new_str = (char *)malloc(sizeof(char) * (ft_lstsize(curr) + 1));
	if (new_str == NULL)
	{
		ft_lstclear(&char_lst, free);
		return (NULL);
	}
	new_str = ft_copy_str(new_str, char_lst);
	ft_lstclear(&char_lst, free);
	return (new_str);
}

#include <stdio.h>
#include <fcntl.h>
int main()
{
	int fd;
	int	i;
	char	*str;

	i = 0;
	str = "123";
	fd = open("libft.a", O_RDONLY);

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

