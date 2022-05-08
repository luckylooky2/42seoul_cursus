CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

LIB=libpush_swap.a
LIB_NAME=push_swap
SOURCE=check_input.c quick_sort.c fill_stack_a.c sort_only_items.c \
		push_swap_utils.c cmd_rotate.c cmd_reverse_rotate.c cmd_push_a.c \
		cmd_push_b.c cmd_swap_a.c cmd_swap_b.c sort_three.c \
		sort_reverse_three.c move_b_to_a_utils.c \
		move_b_to_a.c move_a_to_b.c sort_stack_a.c ft_split.c \
		init_struct.c ft_strjoin.c cmd_swap_s.c push_swap.c
SOURCE_BONUS=get_next_line.c get_next_line_utils.c checker.c
OBJECT=$(SOURCE:.c=.o)
OBJECT_BONUS=$(SOURCE_BONUS:.c=.o)
EXE=push_swap checker



ifdef WITH_BONUS
	NAME=checker
	OBJ = $(OBJECT) $(OBJECT_BONUS)
else
	NAME=push_swap
	OBJ = $(OBJECT)
endif

$(NAME) : $(OBJ)
	$(AR) $(ARFLAGS) $(LIB) $(OBJ)
	$(CC) $(CFLAGS) -L. -l$(LIB_NAME) $(addsuffix  .c, $(NAME)) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

bonus :
	@$(MAKE) all
	@$(MAKE) WITH_BONUS=1 all

clean :
	$(RM) $(OBJECT) $(OBJECT_BONUS)

fclean : clean
	$(RM) $(EXE) $(LIB)

re : fclean all

.PHONY : all clean fclean re bonus
