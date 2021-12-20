CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

NAME=libftprintf.a
SOURCE=ft_printf.c ft_printf_utils.c
SOURCE_BONUS=
OBJECT=$(SOURCE:.c=.o)
OBJECT_BONUS=$(SOURCE_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJ = $(OBJECT) $(OBJECT_BONUS)
else
	OBJ = $(OBJECT)
endif

$(NAME) : $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)

%.o : %.c
	$(CC) $(CFALGS) -c $< -o $@

all : $(NAME)

bonus : 
	@$(MAKE) WITH_BONUS=1 all

clean :
	$(RM) $(OBJECT) $(OBJECT_BONUS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
