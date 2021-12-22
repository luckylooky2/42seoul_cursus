CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

LIBFT_OBJECT=libft/ft_atoi.o libft/ft_bzero.o libft/ft_calloc.o libft/ft_isalnum.o libft/ft_isalpha.o libft/ft_isascii.o libft/ft_isdigit.o libft/ft_isprint.o libft/ft_itoa.o libft/ft_memchr.o libft/ft_memcmp.o libft/ft_memcpy.o libft/ft_memmove.o libft/ft_memset.o libft/ft_putchar_fd.o libft/ft_putendl_fd.o libft/ft_putnbr_fd.o libft/ft_putstr_fd.o libft/ft_split.o libft/ft_strchr.o libft/ft_strdup.o libft/ft_striteri.o libft/ft_strjoin.o libft/ft_strlcat.o libft/ft_strlcpy.o libft/ft_strlen.o libft/ft_strmapi.o libft/ft_strncmp.o libft/ft_strnstr.o libft/ft_strrchr.o libft/ft_strtrim.o libft/ft_substr.o libft/ft_tolower.o libft/ft_toupper.o libft/ft_lstnew.o libft/ft_lstadd_front.o libft/ft_lstsize.o libft/ft_lstlast.o libft/ft_lstadd_back.o libft/ft_lstdelone.o libft/ft_lstclear.o libft/ft_lstiter.o libft/ft_lstmap.o

NAME=libftprintf.a
SOURCE=ft_printf.c print_cspdi.c print_uxX.c ft_printf_utils.c
SOURCE_BONUS=
OBJECT=$(SOURCE:.c=.o)
OBJECT_BONUS=$(SOURCE_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJ = $(OBJECT) $(OBJECT_BONUS)
else
	OBJ = $(OBJECT)
endif

$(NAME) : $(OBJECT)
	@$(MAKE) bonus -C ./libft
	$(AR) $(ARFLAGS) $@ $(OBJECT) $(LIBFT_OBJECT)

%.o : %.c
	$(CC) $(CFALGS) -c $< -o $@

all : $(NAME)

bonus : 
	@$(MAKE) WITH_BONUS=1 all

clean :
	@$(MAKE) fclean -C ./libft
	$(RM) $(OBJECT) $(OBJECT_BONUS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
