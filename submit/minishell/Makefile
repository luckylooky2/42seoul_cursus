# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/27 19:18:22 by youhan            #+#    #+#              #
#    Updated: 2022/07/28 16:08:33 by hangokim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror
LFT_DIR		:=	./libft
LRL_DIR		:=	/Users/$(shell users)/.brew/opt/readline
BT_DIR		:=	./builtins
UTIL_DIR	:=	./utils
EC_DIR		:=	./exec
PARSE_DIR	:=	./parsing
CHECK_DIR	:=	$(PARSE_DIR)/check_error
LIBS		:=	-L$(LRL_DIR)/lib -lreadline -L$(LFT_DIR) -lft
INCS		:=	-I$(LRL_DIR)/include -I$(LFT_DIR) -I.
BT_SRCS		:=	.c cd.c echo.c env.c export.c pwd.c unset.c subshell.c
UTIL_SRCS	:=	env_dict.c global_status.c directory.c heredoc.c make_message.c \
				error_exit.c signal.c delete_funcs1.c delete_funcs2.c \
				regex_matcher.c cleanup_deque.c atoi_strict.c control.c
EC_SRCS		:=	do_exec.c make_proc_pipe.c path.c play_cmd.c redirection.c
PARSE_SRCS	:=	break_semicolon.c break_linker.c break_pipe.c break_space.c \
				make_meaning.c make_syntax.c \
				make_expansions.c make_expansion_env.c make_expansion_asterisk.c \
				remove_redirection.c assign_redirection_flag.c parse_redirection.c
CHECK_SRCS	:=	parsing_error.c check_error.c \
				check_ampersand.c check_error.c check_redirection.c check_subshell.c
SRCS		:=	minishell.c \
				$(BT_SRCS:%.c=$(BT_DIR)/do_builtin_%.c) \
				$(ENV_SRCS:%.c=$(ENV_DIR)/%.c) \
				$(PARSE_SRCS:%.c=$(PARSE_DIR)/%.c) \
				$(CHECK_SRCS:%.c=$(CHECK_DIR)/%.c) \
				$(EC_SRCS:%.c=$(EC_DIR)/%.c) \
				$(UTIL_SRCS:%.c=$(UTIL_DIR)/%.c)
OBJS		:=	$(SRCS:%.c=%.o)
BONUS_OBJS	:=	$(SRCS:%.c=%_bonus.o)

ifndef BONUS
	OBJS_TO_BUILD = $(OBJS)
else
	OBJS_TO_BUILD = $(BONUS_OBJS)
endif

all : $(NAME)

$(NAME) : $(OBJS_TO_BUILD)
	@make -C $(LFT_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(INCS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

clean :
	@make clean -C $(LFT_DIR)
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@make fclean -C $(LFT_DIR)
	rm -f $(NAME)

re: fclean all

bonus:
	@make BONUS=1 all

.PHONY : all clean fclean re bonus
