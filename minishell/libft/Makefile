NAME=libft.a
AR=ar
ARFLAGS=rcus
CC=cc
CFLAGS=-g -Wall -Wextra -Werror
HEADERS=-include libft_utils.h -include libft.h
SOURCES:=isalpha isdigit isalnum isascii isprint \
		 strlen strlcpy strlcat strchr strrchr strncmp strnstr strdup strjoin strtrim strmapi striteri substr\
		 bzero calloc memset memcpy memchr memmove memcmp \
		 atoi itoa split toupper tolower \
		 putchar_fd putstr_fd putendl_fd putnbr_fd \
		 lstnew lstadd_front lstsize lstlast lstadd_back lstdelone lstclear lstiter lstmap \
		 deque deque_utils deq deq_utils \
		 printf gnl printf_get_format printf_conversion printf_utils gnl_utils
SRCS=$(SOURCES:%=ft_%.c)
OBJS=$(SOURCES:%=ft_%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
