# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/27 19:18:22 by youhan            #+#    #+#              #
#    Updated: 2022/07/26 23:32:21 by chanhyle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= 	cc
CFLAGS		:= 	-g3 -DDEBUG_MODE #-Wall -Wextra -Werror
LFT_DIR		:= 	./libft
LRL_DIR		:= 	/Users/$(shell users)/.brew/opt/readline
BT_DIR		:= 	./builtins
UTIL_DIR	:=	./utils
EC_DIR		:=	./exec
PARSE_DIR	:= ./parsing
LIBS		:= 	-L$(LRL_DIR)/lib -lreadline -L$(LFT_DIR) -lft
INCS		:= 	-I$(LRL_DIR)/include -I$(LFT_DIR) -I.
BT_SRCS		:=	
UTIL_SRCS	:= 	signal.c
PARSE_SRCS	:=	
SRCS		:=	minishell.c \
				test_module.c \
				$(BT_SRCS:%.c=$(BT_DIR)/%.c) \
				$(ENV_SRCS:%.c=$(ENV_DIR)/%.c) \
				$(PARSE_SRCS:%.c=$(PARSE_DIR)/%.c) \
				$(EC_SRCS:%.c=$(EC_DIR)/%.c) \
				$(UTIL_SRCS:%.c=$(UTIL_DIR)/%.c)
OBJS		:= $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJS)
	# make -C $(LFT_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(INCS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

clean :
	# make clean -C $(LFT_DIR)
	rm -f $(OBJS)

fclean: clean
	# make fclean -C $(LFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re bonus
