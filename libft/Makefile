CC=gcc
AR=ar
OPTIONS=rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

NAME=libft.a
SOURCE=ft_libc_1.c ft_libc_2.c ft_libc_3.c ft_libc_4.c ft_libc_5.c ft_additional_1.c ft_additional_2.c ft_additional_3.c ft_additional_4.c
OBJECT=$(SOURCE:.c=.o)

.c.o :
	$(CC) $(CFALGS) -c $< -o $(<:.c=.o)

$(NAME) : $(OBJECT)
	$(AR) $(OPTIONS) $(NAME) $(OBJECT)

all : $(NAME)

clean :
	$(RM) $(OBJECT)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean .c.o
