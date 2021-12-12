/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:44:09 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/12 16:10:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*make_linked_list(char *buf, t_list *char_lst)
{
	char	*new_char;

	new_char = (char *)malloc(sizeof(char));
	if (new_char == NULL)
	{
		ft_lstclear(&char_lst, free);
		return (NULL);
	}
	*new_char = *buf;
	make_new_node(&char_lst, new_char);
	return (char_lst);
}

static int	check_repeat_break(char *buf, int fd, int *index, int read_size)
{
	if (*index == BUFFER_SIZE && buf[*index - 1] == '\n' && read_size > 0)
	{
		*index = 0;
		return (1);
	}
	else if (*index == BUFFER_SIZE && read_size > 0)
	{
		*index = 0;
		return (0);
	}
	else
		return (1);
}

static char	*copy_linked_list(t_list *char_lst, char *new_str)
{
	int		i;

	i = 0;
	while (char_lst)
	{
		new_str[i++] = *((char *)((char_lst)->content));
		char_lst = (char_lst)->next;
	}
	new_str[i] = '\0';
	return (new_str);
}

static char	*make_new_string(char **buf, t_list *char_lst, int read_size)
{
	char	*new_str;
	int		lst_len;

	if (*buf == NULL)
		return (NULL);
	lst_len = ft_lstsize(char_lst);
	new_str = (char *)malloc(sizeof(char) * (lst_len + 1));
	if (new_str == NULL || read_size == -1)
		ft_lstclear(&char_lst, free);
	if (char_lst == NULL || read_size == -1)
		free(new_str);
	if (new_str == NULL || char_lst == NULL || read_size == -1)
	{
		free(*buf);
		*buf = NULL;
		return (NULL);
	}
	new_str = copy_linked_list(char_lst, new_str);
	ft_lstclear(&char_lst, free);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	static int	index;
	static int	read_size;
	t_list		*char_lst;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	char_lst = NULL;
	if (buf == NULL)
		buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	while (buf != NULL)
	{
		if (index == 0)
			read_size = read(fd, buf, BUFFER_SIZE);
		while (index < read_size)
		{
			char_lst = make_linked_list(&buf[index++], char_lst);
			if (char_lst == NULL || buf[index - 1] == '\n')
				break ;
		}
		if (char_lst == NULL || check_repeat_break(buf, fd, &index, read_size))
			break ;
	}
	return (make_new_string(&buf, char_lst, read_size));
}
