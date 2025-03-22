FLAG = -Wall -Wextra -Werror

NAME = libft.a

SRC = \
    ft_strlen.c \
    ft_strnstr.c \
    ft_strdup.c \
    ft_strjoin.c \
    ft_putendl_fd.c \
    ft_split.c \
    ft_itoa.c \
    ft_isdigit.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "$(NAME) created"
	@ranlib $(NAME)
	@echo "$(NAME) indexed"

%.o: %.c
	@gcc $(FLAG) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "OBJ deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

re: fclean all

.PHONY: all clean fclean re
