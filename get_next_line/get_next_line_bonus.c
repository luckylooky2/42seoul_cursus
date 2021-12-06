/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:36:00 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/05 21:06:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static t_list	*make_new_node(t_list *char_lst, char *buf)
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

static int	check_repeat_or_break(char *buf, char **curr, int read_size)
{
	if ((*curr == buf + BUFFER_SIZE) && *(*curr - 1) == '\n')
	{
		*curr = *curr - BUFFER_SIZE;
		return (1);
	}
	else if ((*curr == buf + BUFFER_SIZE) && read_size > 0)
	{
		*curr = *curr - BUFFER_SIZE;
		return (0);
	}
	else
		return (1);
}

static char	*copy_str(char *new_str, t_list *char_lst)
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

static char	*make_new_str(int fd, t_list *char_lst, int read_size)
{
	char	*new_str;
	t_list	*curr;
	int		lst_len;

	lst_len = 0;
	curr = char_lst;
	while (curr)
	{
		curr = curr->next;
		lst_len++;
	}
	new_str = (char *)malloc(sizeof(char) * (lst_len + 1));
	if (new_str == NULL || char_lst == NULL
		|| fd < 0 || fd > OPEN_MAX || read_size == -1 || BUFFER_SIZE <= 0)
	{
		ft_lstclear(&char_lst, free);
		free(new_str);
		return (NULL);
	}
	new_str = copy_str(new_str, char_lst);
	ft_lstclear(&char_lst, free);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*new_str;
	t_list		*char_lst;
	int			read_size;

	char_lst = NULL;
	read_size = 0;
	while (0 <= fd && fd <= OPEN_MAX && BUFFER_SIZE > 0)
	{
		if (*buf == '\0')
		{
			ft_memset(buf, 0, BUFFER_SIZE + 1);
			read_size = read(fd, buf, BUFFER_SIZE);
			// printf("size : %d\n", read_size);
			// printf("%c\n", *curr);
		}
		// printf("%p, %p\n", curr, buf + BUFFER_SIZE);
		// printf("%d\n", read_size);
		// printf("%c\n", *curr);
		while (*buf != '\0' && read_size > 0)
		{
			// printf("%p %p", curr, buf + BUFFER_SIZE);
			char_lst = make_new_node(char_lst, buf++);
			// printf("%c", *curr);
			if (char_lst == NULL || *(curr - 1) == '\n')
				break ;
		}
		if (check_repeat_or_break(buf, &curr, read_size) == 1)
			break ;
	}
	new_str = make_new_str(fd, char_lst, read_size);
	return (new_str);
}

#include <stdio.h>
#include <fcntl.h>
int main()
{
	char *str = "!23";
	int fd = open("a.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
}