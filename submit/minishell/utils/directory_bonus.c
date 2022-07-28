/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:09:56 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:59:02 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static DIR	*init_dirp(void)
{
	DIR	*dirp;

	dirp = opendir(".");
	if (dirp == NULL)
	{
		if (errno == ENOMEM)
			panic_memory();
		else
		{
			error_handle("cannot access current directory.");
			return (NULL);
		}
	}
	return (dirp);
}

t_dirent	*get_next_dir(t_dir_cmd cmd)
{
	static DIR		*dirp = NULL;
	t_dirent		*dir;

	if (cmd == INIT_DIR)
		dirp = init_dirp();
	else if (cmd == CLOSE_DIR)
	{
		if (dirp != NULL)
			closedir(dirp);
		dirp = NULL;
	}
	else if (cmd == GET_DIR)
	{
		if (dirp != NULL)
		{
			dir = readdir(dirp);
			if (dir == NULL && \
			(errno == EBADF || errno == EIO || errno == EFAULT))
				error_errno("readdir");
			return (dir);
		}
	}
	return ((t_dirent *)dirp);
}
