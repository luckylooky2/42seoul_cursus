CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

NAME=push_swap
LIB=libpush_swap.a
MAIN=push_swap.c
SOURCE=check_input.c quick_sort.c fill_stack_a.c sort_only_items.c \
		push_swap_utils.c cmd_rotate.c cmd_reverse_rotate.c cmd_push_a.c \
		cmd_push_b.c cmd_swap_a.c cmd_swap_b.c sort_three.c \
		sort_reverse_three.c move_b_to_a_utils.c \
		move_b_to_a.c move_a_to_b.c sort_stack_a.c ft_split.c \
		init_struct.c ft_strjoin.c 
# SOURCE_BONUS=
OBJECT=$(SOURCE:.c=.o)
OBJECT_MAIN=$(MAIN:.c=.o)
OBJECT_BONUS=$(SOURCE_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJ = $(OBJECT_BONUS)
else
	OBJ = $(OBJECT) $(OBJECT_MAIN)
endif

$(NAME) : $(OBJ)
	$(AR) $(ARFLAGS) $(LIB) $(OBJECT)
	$(CC) $(CFLAGS) -L. -l$(NAME) $(MAIN) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

bonus : 
	@$(MAKE) WITH_BONUS=1 all

clean :
	$(RM) $(OBJECT) $(OBJECT_MAIN) $(OBJECT_BONUS) $(LIB)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
