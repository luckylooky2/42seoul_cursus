/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:13:17 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/22 20:50:26 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_str_array(char **arr)
{
	int	cnt;

	cnt = 0;
	while (arr[cnt])
		cnt++;
	return (cnt);
}

static void	shift_str_array(char **arr, int i)
{
	free(arr[i]);
	while (arr[i])
	{
		arr[i] = arr[i + 1];
		i++;
	}
}

static int	is_valid(char *name, int length)
{
	int		i;

	if (length == 0)
		return (0);
	i = 0;
	if ('0' <= name[0] && name[0] <= '9')
		return (0);
	while (i < length)
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_declare_x_list(void)
{
	char	**list;
	int		i;

	list = (char **)env_commands(LIST_ENV, NULL);
	if (list == NULL)
		panic_memory();
	i = 0;
	while (list[i])
		printf("declare -x %s\n", list[i++]);
	delete_str_array(list);
}

void	do_builtin_export(char **argv)
{
	int		i;
	char	*delim;
	char	*temp;
	char	*message;

	if (count_str_array(argv) == 1)
		return (print_declare_x_list());
	i = -0;
	while (argv[++i])
	{
		delim = ft_strchr(argv[i], '=');
		if (delim == NULL || !is_valid(argv[i], delim - argv[i]))
		{
			temp = ft_strjoin("export: `", argv[i]);
			message = ft_strjoin(temp, "': not a valid identifier.");
			free(temp);
			error_handle(message);
			free(message);
			shift_str_array(argv, i);
			global_status(SET_STATUS, 1);
		}
		else
			global_status(SET_STATUS, 0);
	}
	env_commands(PUT_ENV, argv + 1);
}
