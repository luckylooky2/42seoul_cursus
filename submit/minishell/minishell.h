/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:12:40 by youhan            #+#    #+#             */
/*   Updated: 2022/07/26 19:37:10 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"
# include "minishell_enums.h"

/** parsing structs **/
typedef struct s_syntax
{
	char	*input;
	char	*meaning;
}	t_syntax;

typedef struct s_data
{
	int		infile_num;
	int		outfile_num;
	int		cmd_num;
	char	*rd_flag;
	char	check;
}	t_data;

typedef struct s_command
{
	t_syntax	*syntax;
	char		**argv;
	t_deq		*input;
	t_deq		*output;
}	t_command;

typedef struct s_commands
{
	t_syntax	*syntax;
	t_deq		*piped_commands;
	t_link		prev;
}	t_commands;

/** env structs **/
typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

/** exec struct **/
typedef struct s_state
{
	pid_t	*pid;
	int		**pipes;
	int		pid_cnt;
	int		pipe_cnt;
	char	**path;
	char	builtin_flag;
}	t_state;

/** functions **/
void			do_exec(t_deq *commands);
void			panic(char *message);
void			panic_memory(void);
void			error_exit(char *command);
void			error_handle(char *message);
void			error_errno(char *prefix);
char			*env_commands(t_env_cmd cmd, char **argv);
int				global_status(t_global_cmd cmd, int value);
int				regex_matcher(char *input, char *regex);
void			process_heredoc(t_syntax *syntax);
char			*heredoc_manager(t_heredoc_cmd cmd, char *delimiter);
void			control_in_and_out(t_control c);
t_deq			*cleanup_deque(t_deq *deq, void del(void *));
t_dirent		*get_next_dir(t_dir_cmd cmd);
int				atoi_s(const char *str, char *flag);
char			*make_message(char *prefix, char *message, char *suffix);
char			*make_temp_file_name(char *path, int id);

// delete functions
void			delete_linked_commands(void *l_cmd);
void			delete_str_array(void *arr);
void			delete_t_command(void *cmd);
void			delete_t_commands(void *cmd);
void			delete_t_env(void *arg);
void			delete_t_syntax(void *arg);
void			delete_t_state(void *arg);
void			delete_temp_file(void *str);

// signals
t_sig_handler	ft_signal(int signum, t_sig_handler handler);
void			sigint_handler(int signum);
void			sigquit_handler(int signum);

// builtins
t_builtin		get_builtin_enum(char **argv);
void			do_builtin(char **argv);
void			do_builtin_cd(char **argv);
void			do_builtin_echo(char **argv);
void			do_builtin_env(char **argv);
void			do_builtin_export(char **argv);
void			do_builtin_pwd(char **argv);
void			do_builtin_subshell(char **argv);
void			do_builtin_unset(char **argv);
int				is_command_subshell(char *arg);

// exec functions
void			play_cmd(t_state *s, char **env, t_deq *commands);
void			make_proc_pipe(t_state *s);
char			**path_check(char *env);
char			*find_cmd_in_path(t_state *s, char *cmd);
int				input_redirection(t_state *s, t_deq *output_files, int n);
int				output_redirection(t_state *s, t_deq *output_files, int n);

// parsing functions
t_deq			*parse_args(char *input, t_subject subject);
char			*make_meaning(char *input);
t_syntax		*syntax_from_input(char *input, char *meaning);
t_syntax		*slice_syntax(t_syntax *s, int i, int length, t_delimiter d);
void			insert_syntax(t_syntax *s1, t_syntax *s2, int i);
t_deq			*break_semicolon(t_syntax *s);
void			break_linker(t_deq *broken_semicolon);
void			break_pipe(t_deq *broken_semicolon);
char			**break_space(t_syntax *syntax);
char			**break_space_const(t_syntax *s);
t_deq			*make_expansions(t_deq	*piped_commands);
void			expand_env(t_syntax *s, int i);
void			expand_asterisk(t_syntax *s, int i);
void			remove_redirection(t_syntax *syntax, t_command *cmd);
void			assign_redirection_flag(t_syntax *syn, t_data *data);
void			parse_redirection(t_syntax *syn, t_data *data, t_command *cmd);

// parsing checking, error functions
int				parsing_error_on_syntax(t_syntax *syntax);
void			parsing_error(t_syntax *syntax, char *token, int i);
int				there_is_only_one_ampersand(t_syntax *s);
int				there_are_redirection_parsing_error(t_syntax *s);
int				there_are_subshell_parsing_error(t_syntax *syntax);
int				there_are_parse_error_in_subshell(t_syntax *s);

#endif
