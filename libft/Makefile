# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 10:46:20 by chanhyle          #+#    #+#              #
#    Updated: 2021/11/23 10:46:30 by chanhyle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
AR=ar
OPTIONS=rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

NAME=libft.a
SOURCE=ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
SOURCE_BONUS=ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c 
OBJECT=$(SOURCE:.c=.o)
OBJECT_BONUS=$(SOURCE_BONUS:.c=.o)

ifndef BONUS
	OBJECT_FILES = $(OBJECT) $(OBJECT_BONUS)
else
	OBJECT_FILES = $(OBJECT)
endif

%.o : %.c
	$(CC) $(CFALGS) -c $< -o $(<:.c=.o)

$(NAME) : $(OBJECT)
	$(AR) $(OPTIONS) $@ $(OBJECT_FILES)

all : $(NAME)

bonus : BONUS=1 all

clean :
	$(RM) $(OBJECT) $(OBJECT_BONUS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re .c.o
