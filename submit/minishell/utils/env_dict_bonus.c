/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dict_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:59:08 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:59:04 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static char	*get_env(const t_deq *env_list, char *key);
static void	put_env(t_deq *env_list, char **env_str_list);
static void	del_env(t_deq *env_list, char **keys);
static char	**list_env(t_deq *env_list);

char	*env_commands(t_env_cmd cmd, char **argv)
{
	static t_deq	*env_list = NULL;

	if (env_list == NULL)
	{
		env_list = ft_deq_new();
		if (env_list == NULL)
			panic("Failed to initialize env list.");
	}
	if (cmd == GET_ENV)
		return (get_env(env_list, *argv));
	else if (cmd == PUT_ENV)
		put_env(env_list, argv);
	else if (cmd == DELETE_ENV)
		del_env(env_list, argv);
	else if (cmd == LIST_ENV)
		return ((char *)list_env(env_list));
	else if (cmd == CLOSE_ENV)
		ft_deq_delete(&env_list, delete_t_env);
	return (NULL);
}

static char	*get_env(const t_deq *env_list, char *key)
{
	t_gnode	*node;
	t_env	*env;

	node = env_list->tail->next;
	while (node != env_list->tail)
	{
		env = node->data;
		if (ft_strncmp(env->key, key, ft_strlen(env->key) + 1) == 0)
			return (env->value);
		node = node->next;
	}
	return (NULL);
}

static void	put_env(t_deq *env_list, char **env_str_list)
{
	static char	*buffer[2] = {0, };
	char		*value;
	t_env		*new_env;

	while (*env_str_list)
	{
		value = ft_strchr(*env_str_list, '=');
		if (value == NULL)
		{
			env_str_list++;
			continue ;
		}
		*value++ = 0;
		buffer[0] = *env_str_list;
		del_env(env_list, buffer);
		new_env = (t_env *)malloc(sizeof(t_env));
		if (new_env == NULL)
			panic_memory();
		new_env->key = ft_strdup(*env_str_list++);
		new_env->value = ft_strdup(value);
		if (new_env->key == NULL || new_env->value == NULL || \
		ft_deq_push_back(env_list, new_env) == -1)
			panic_memory();
	}
}

static void	del_env(t_deq *env_list, char **keys)
{
	int		i;
	t_gnode	*cur;
	t_env	*env;

	i = 0;
	while (keys[i])
	{
		cur = env_list->tail->next;
		while (cur != env_list->tail)
		{
			env = cur->data;
			if (ft_strncmp(env->key, keys[i], ft_strlen(env->key) + 1) == 0)
			{
				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
				delete_t_env(env);
				free(cur);
				env_list->size--;
				break ;
			}
			cur = cur->next;
		}
		i++;
	}
}

static char	**list_env(t_deq *env_list)
{
	char	**result;
	char	*env_str;
	t_env	*env;
	size_t	i;

	result = (char **)malloc((env_list->size + 1) * sizeof(char *));
	if (result == NULL)
		panic_memory();
	i = 0;
	while (i < env_list->size)
	{
		env = ft_deq_get(env_list, i)->data;
		env_str = (char *)malloc((ft_strlen(env->key) + ft_strlen(\
		env->value) + 2) * sizeof(char));
		if (env_str == NULL)
			panic_memory();
		ft_strlcpy(env_str, env->key, ft_strlen(env->key) + 1);
		env_str[ft_strlen(env->key)] = '=';
		ft_strlcpy(env_str + ft_strlen(env->key) + 1, env->value, \
		ft_strlen(env->value) + 1);
		result[i++] = env_str;
	}
	result[i] = 0;
	return (result);
}
