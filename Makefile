# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
# CC = gcc
# CFLAGS =  -g
NAME = minishell

LIBS = -lreadline -Llibft -lft  # Link to the libft library (-lft) and readline
#-Wall -Wextra -Werror
# Files
SRC = cd.c \
      echo.c \
      env.c \
      error_handling.c \
      exit.c \
      export.c \
      free.c \
      heredoc_expand.c \
      input_error_handling.c \
      main.c \
      pwd.c \
      quotes.c \
      signals.c \
      token_split.c \
      tokenization.c \
      unset.c \
      updated_tokenization.c \
      utils_1.c \
      builtins/cd_helper.c \
      builtins/cd.c \
      dups/dups.c \
      dups/dups_helper.c \
      dups/dups_helper1.c \
      execution/execution1.c \
      execution/execution2.c \
      expand_dollar/dollar.c \
      expand_dollar/dollar1.c \
      expand_dollar/dollar2.c \

# $(wildcard *.c) $(wildcard expand_dollar/*.c builtins/*.c dups/*.c execution/*.c)
OBJ = $(SRC:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(OBJ) libft/libft.a  # Ensure libft is built before linking
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

libft/libft.a:  # Build libft if it doesn't exist or needs to be updated
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C libft clean  # Clean libft object files as well

fclean: clean
	rm -f $(NAME)
	make -C libft fclean  # Clean libft executables as well

re: fclean all  # Rebuild everything