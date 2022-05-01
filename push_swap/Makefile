CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

NAME=push_swap.a
SOURCE=push_swap.c
SOURCE_BONUS=
OBJECT=$(SOURCE:.c=.o)
OBJECT_BONUS=$(SOURCE_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJ = $(OBJECT_BONUS)
else
	OBJ = $(OBJECT)
endif

$(NAME) : $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJECT)

%.o : %.c
	@$(CC) -c $< -o $@

all : $(NAME)

bonus : 
	@$(MAKE) WITH_BONUS=1 all

clean :
	$(RM) $(OBJECT) $(OBJECT_BONUS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
