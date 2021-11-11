CC=gcc // ar 명령어로 바꿀 것
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

NAME=libft
SOURCE=srcs/ft_main.c srcs/ft_tail.c srcs/ft_option.c srcs/ft_split.c srcs/ft_extra.c srcs/ft_extra_2.c
OBJECT=$(SOURCE:.c=.o)

$(NAME) :
	$(CC) $(CFALGS) -c $< -o $(<:.c=.o) -Iincludes

all : $(NAME)

clean :
	$(RM) $(OBJECT)

fclean : clean
	$(RM) $(NAME)

re : ?
	?

.PHONY : all clean fclean .c.o
