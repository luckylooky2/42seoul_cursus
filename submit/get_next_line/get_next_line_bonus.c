/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:11:25 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/09 18:38:41 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	rearrange_string(char *buf)
{
	int	index;
	int	new_index;

	index = 0;
	new_index = 0;
	if (buf == NULL || buf[index] == '\0')
		return (0);
	while (index < BUFFER_SIZE && buf[index] != '\n' && buf[index] != '\0')
		index++;
	if (buf[index] == '\n')
		index++;
	while (index < BUFFER_SIZE + 1)
	{
		buf[new_index] = buf[index];
		if (buf[index] == '\0')
			break ;
		new_index++;
		index++;
	}
	return (0);
}

static t_list	*make_new_node(t_list *char_lst, char *buf)
{
	char	*new_char;
	t_list	*new_node;

	if (buf[0] == '\0')
		return (NULL);
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

static int	check_repeat_or_break(char *buf, int index)
{
	if (index == 0)
		return (1);
	if ((buf[index] == '\0' && buf[index - 1] == '\n')
		|| (buf[index] == '\0' && buf[index - 1] == '\0'))
	{
		ft_memset(buf, 0, BUFFER_SIZE + 1);
		return (1);
	}
	else if (buf[index] == '\0' && buf[index - 1] != '\n')
	{
		ft_memset(buf, 0, BUFFER_SIZE + 1);
		return (0);
	}
	else
		return (1);
}

static char	*make_new_string(t_list *char_lst, int read_size)
{
	char	*new_str;
	t_list	*curr;
	int		i;

	i = 0;
	curr = char_lst;
	new_str = (char *)malloc(sizeof(char) * (ft_lstsize(char_lst) + 1));
	if (new_str == NULL || char_lst == NULL || read_size == -1)
	{
		ft_lstclear(&char_lst, free);
		free(new_str);
		return (NULL);
	}
	while (curr)
	{
		new_str[i] = *((char *)((curr)->content));
		curr = (curr)->next;
		i++;
	}
	new_str[i] = '\0';
	ft_lstclear(&char_lst, free);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*buf[10241];
	char		*new_str;
	t_list		*char_lst;
	int			index;
	int			read_size;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	char_lst = NULL;
	read_size = 0;
	if (buf[fd] == NULL)
		buf[fd] = (char *)calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (buf[fd] == NULL)
			return (NULL);
	while (1)
	{
		index = rearrange_string(buf[fd]);
		if (buf[fd][0] == '\0')
			read_size = read(fd, buf[fd], BUFFER_SIZE);
		while (index < BUFFER_SIZE && buf[fd][index] != '\0' && read_size != -1)
		{
			char_lst = make_new_node(char_lst, &buf[fd][index++]);
			if (char_lst == NULL || buf[fd][index - 1] == '\n')
				break ;
		}
		if (check_repeat_or_break(buf[fd], index) == 1 || char_lst == NULL)
			break ;
	}
	new_str = make_new_string(char_lst, read_size);
	if (buf[fd][index] == '\0')
	{
		free(buf[fd]);
		buf[fd] = NULL;
	}
	return (new_str);
}
