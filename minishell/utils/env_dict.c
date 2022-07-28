/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dict.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 23:56:08 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 15:09:20 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_env(const t_deq *env_list, char *key);
static void	put_env(t_deq *env_list, char **env_str_list);
static void	del_env(t_deq *env_list, char **keys);
static char	**list_env(t_deq *env_list);

/* (static) 전역으로 환경 변수를 관리하는 함수 모듈 */
/* enum을 쓰는 방식
	1. 헤더 파일에 정의
	2. 전처리 #define 쓰듯이 인자로 넘겨줄 때 넘겨줌
	3. 함수 내에서 받아서 마찬가지로 #define 쓰듯이 typedef enum 자료형으로 씀 */
char	*env_commands(t_env_cmd cmd, char **argv)
{
	static t_deq	*env_list = NULL;
	
	if (env_list == NULL) // 제일 처음 들어올 때
	{
		env_list = ft_deq_new(); // 환경 변수용 deq 생성
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
		return ((char *)list_env(env_list)); // 잠시 char *포인터로 바꿈, 포인터끼리 변경하는 것이기 때문에 나중에 되돌려 놓으면 됨
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
		env = node->data; // 가져오는 것이기 때문에 data를 자리키는 포인터
		if (ft_strncmp(env->key, key, ft_strlen(env->key) + 1) == 0) // key를 비교
			return (env->value);
		node = node->next;
	}
	return (NULL);
}

// 현재 환경 변수로 env_list를 초기화하는 함수
static void	put_env(t_deq *env_list, char **env_str_list)
{
	static char *buffer[2] = {0, };
	char		*value;
	t_env		*new_env;

	while (*env_str_list) // envp[i]를 순회
	{
		value = ft_strchr(*env_str_list, '='); // = 찾기
		if (value == '\0')
		{
			env_str_list++;
			continue;
		}
		*value++ = '\0'; // key와 value를 나눔
		if (get_env(env_list, *env_str_list) != NULL) // env_list에 일치하는 것이 있다면, envp로 초기화
		{
			buffer[0] = *env_str_list; // key만 저장하기 위해
			del_env(env_list, buffer); // 원래 값 삭제
		}
		new_env = (t_env *)malloc(sizeof(t_env));
		if (new_env == NULL)
			panic_memory();
		new_env->key = ft_strdup(*env_str_list++); // *env_str_list 상의 key index(0)
		new_env->value = ft_strdup(value); // *env_str_list 상의 value index
		if (new_env->key == NULL || new_env->value == NULL)
			panic_memory();
		ft_deq_push_back(env_list, new_env);
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
			if (ft_strncmp(env->key, keys[i], ft_strlen(env->key) + 1) == 0) // key를 비교
			{
				cur->prev->next = cur->next;
				cur->next->prev - cur->prev;
				delete_t_env(env); // 해당 env를 free()
				env_list->size--;
				break ;
			}
			cur = cur->next;
		}
		i++;
	}
}

// 현재 환경 변수를 char **로 복사하여 생성하는 함수 => 언제 쓰이나?
static char	**list_env(t_deq *env_list)
{
	char	**result;
	char	*env_str;
	t_env	*env;
	int		i;

	result = (char **)malloc((env_list->size + 1) * sizeof(char *));
	if (result == 0)
		panic_memory();
	i = 0;
	while (i < (int)env_list->size)
	{
		env = ft_deq_get(env_list, i)->data;
		env_str = (char *)malloc(sizeof(char) * (ft_strlen(env->key) + ft_strlen(env->value) + 2));
		if (env_str == NULL)
			panic_memory();
		ft_strlcpy(env_str, env->key, ft_strlen(env->key) + 1); // key 복사
		env_str[ft_strlen(env->key)] = '='; // '=' 복사
		ft_strlcpy(env_str + ft_strlen(env->key) + 1, env->value, ft_strlen(env->value) + 1); // value 복사
		result[i++] = env_str; // 복사 완료한 char *을 result에 연결
	}
	result[i] = NULL;
	return (result);
}
