CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

LIB=fdf
SRC_DIR=src
SRC_BONUS_DIR=src_bonus
SRC=$(addprefix $(SRC_DIR)/, fdf.c get_next_line.c get_next_line_utils.c)
SRC_BONUS=$(addprefix $(SRC_BONUS_DIR)/,)
OBJECT=$(SRC:.c=.o)
OBJECT_BONUS=$(SRC_BONUS:.c=.o)
EXE=fdf

ifdef WITH_BONUS
	NAME=checker
	FILE=checker_bonus
	OBJ = $(OBJECT) $(OBJECT_BONUS)
	DIR = $(SRC_BONUS_DIR)
else
	NAME=fdf
	FILE=fdf
	OBJ = $(OBJECT)
	DIR = $(SRC_DIR)
endif

$(NAME) : $(OBJ)
	$(AR) $(ARFLAGS) $(addprefix lib, $(addsuffix .a, $(LIB))) $(OBJ)
	$(CC) $(CFLAGS) -g -L. -l$(LIB) -Iinclude $(DIR)/$(addsuffix .c, $(FILE)) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -g -c $< -o $@

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
