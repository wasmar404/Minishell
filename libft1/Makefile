FLAG = -Wall -Wextra -Werror

NAME = libft.a

SRC = ft_isalpha.c \
    ft_isdigit.c \
    ft_isalnum.c \
    ft_isascii.c \
    ft_isprint.c \
    ft_strlen.c \
    ft_memset.c \
    ft_bzero.c \
    ft_memcpy.c \
    ft_memmove.c \
    ft_strlcpy.c \
    ft_strlcat.c \
    ft_toupper.c \
    ft_tolower.c \
    ft_strchr.c \
    ft_strrchr.c \
    ft_memchr.c \
    ft_memcmp.c \
    ft_strnstr.c \
    ft_atoi.c \
    ft_calloc.c \
    ft_strdup.c \
    ft_substr.c \
    ft_strncmp.c \
    ft_strjoin.c \
    ft_strtrim.c \
    ft_putchar_fd.c \
    ft_putstr_fd.c \
    ft_putendl_fd.c \
    ft_putnbr_fd.c \
    ft_strmapi.c \
    ft_striteri.c \
    ft_split.c \
    ft_itoa.c \
    
OBJ = $(SRC:.c=.o)

BONUS_SRC = ft_lstnew_bonus.c \
            ft_lstadd_front_bonus.c \
            ft_lstsize_bonus.c \
            ft_lstlast_bonus.c \
            ft_lstadd_back_bonus.c \
            ft_lstdelone_bonus.c \
            ft_lstclear_bonus.c \
            ft_lstiter_bonus.c \
            ft_lstmap_bonus.c \
            
BONUS = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(BONUS)
	@ar rc $(NAME) $(OBJ) $(BONUS)
	@echo "$(NAME) created"
	@ranlib $(NAME)
	@echo "$(NAME) indexed"
    
%.o: %.c
	@gcc $(FLAG) -c $< -o $@
    
clean:
	@rm -f $(OBJ) $(BONUS)
	@echo "OBJ deleted"
    
fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"
    
re: fclean all

bonus: $(OBJ) $(BONUS)
	@ar rc $(NAME) $(OBJ) $(BONUS)
    
.PHONY: all, clean, fclean, re
