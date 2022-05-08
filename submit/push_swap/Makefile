CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

LIB=push_swap
SRC_DIR=src
SRC_BONUS_DIR=src_bonus
SRC=$(addprefix $(SRC_DIR)/, check_input.c quick_sort.c fill_stack_a.c \
	sort_only_items.c push_swap_utils.c cmd_rotate.c cmd_reverse_rotate.c \
	cmd_push_a.c cmd_push_b.c cmd_swap_a.c cmd_swap_b.c sort_three.c \
	sort_reverse_three.c move_b_to_a_utils.c \
	move_b_to_a.c move_a_to_b.c sort_stack_a.c ft_split.c \
	init_struct.c ft_strjoin.c cmd_swap_s.c push_swap.c)
SRC_BONUS=$(addprefix $(SRC_BONUS_DIR)/, get_next_line_bonus.c \
	get_next_line_utils_bonus.c checker_bonus.c)
OBJECT=$(SRC:.c=.o)
OBJECT_BONUS=$(SRC_BONUS:.c=.o)
EXE=push_swap checker

ifdef WITH_BONUS
	NAME=checker
	FILE=checker_bonus
	OBJ = $(OBJECT) $(OBJECT_BONUS)
	DIR = $(SRC_BONUS_DIR)
else
	NAME=push_swap
	FILE=push_swap
	OBJ = $(OBJECT)
	DIR = $(SRC_DIR)
endif

$(NAME) : $(OBJ)
	$(AR) $(ARFLAGS) $(addprefix lib, $(addsuffix .a, $(LIB))) $(OBJ)
	$(CC) $(CFLAGS) -L. -l$(LIB) -Iinclude $(DIR)/$(addsuffix .c, $(FILE)) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

bonus :
	@$(MAKE) all
	@$(MAKE) WITH_BONUS=1 all

clean :
	$(RM) $(OBJECT) $(OBJECT_BONUS)

fclean : clean
	$(RM) $(EXE) $(addprefix lib, $(addsuffix .a, $(LIB)))

re : fclean all

.PHONY : all clean fclean re bonus
