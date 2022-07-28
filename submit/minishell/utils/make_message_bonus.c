/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_message_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 23:57:55 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:59:13 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

char	*make_message(char *prefix, char *message, char *suffix)
{
	char	*full_message;
	char	*message_with_prefix;

	message_with_prefix = ft_strjoin(prefix, message);
	if (message_with_prefix == NULL)
		panic_memory();
	full_message = ft_strjoin(message_with_prefix, suffix);
	if (full_message == NULL)
		panic_memory();
	free(message_with_prefix);
	return (full_message);
}

char	*make_temp_file_name(char *path, int id)
{
	char	*file_name;
	char	*id_str;

	id_str = ft_itoa(id);
	if (id_str == NULL)
		panic_memory();
	file_name = ft_strjoin(path, id_str);
	if (file_name == NULL)
		panic_memory();
	free(id_str);
	return (file_name);
}
