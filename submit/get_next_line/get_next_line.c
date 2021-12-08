/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:44:09 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/08 13:44:13 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static int	check_repeat_or_break(char *buf, int *index, int read_size)
{
	if ((*index == BUFFER_SIZE) && buf[*index - 1] == '\n' && read_size > 0)
	{
		*index = 0;
		return (1);
	}
	else if ((*index == BUFFER_SIZE) && read_size > 0)
	{
		*index = 0;
		return (0);
	}
	else
		return (1);
}

static char	*make_new_str(int fd, t_list *char_lst, int read_size)
{
	char	*new_str;
	t_list	*curr;
	int		lst_len;
	int		i;

	i = 0;
	curr = char_lst;
	lst_len = ft_lstsize(char_lst);
	new_str = (char *)malloc(sizeof(char) * (lst_len + 1));
	if (new_str == NULL || char_lst == NULL
		|| fd < 0 || fd > OPEN_MAX || read_size == -1 || BUFFER_SIZE <= 0)
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
	static char	buf[BUFFER_SIZE];
	static int	index;
	static int	read_size;
	char		*new_str;
	t_list		*char_lst;

	char_lst = NULL;
	while (0 <= fd && fd <= OPEN_MAX && BUFFER_SIZE > 0)
	{
		if (index == 0)
			read_size = read(fd, buf, BUFFER_SIZE);
		while (index < read_size)
		{
			char_lst = make_new_node(char_lst, &buf[index]);
			index++;
			if (char_lst == NULL || buf[index - 1] == '\n')
				break ;
		}
		if (check_repeat_or_break(buf, &index, read_size) == 1)
			break ;
	}
	new_str = make_new_str(fd, char_lst, read_size);
	return (new_str);
}
