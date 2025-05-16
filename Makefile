# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = minishell

LIBS = -lreadline -Llibft -lft

# Object directory
OBJDIR = obj

# Source files
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
      expand_dollar/dollar2.c

# Object files
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

# Default rule
all: $(NAME)

# Link the binary
$(NAME): $(OBJ) libft/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

# Compile object files into OBJDIR
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft
libft/libft.a:
	make -C libft

# Clean object files
clean:
	rm -rf $(OBJDIR)
	make -C libft clean

# Clean everything
fclean: clean
	rm -f $(NAME)
	make -C libft fclean

# Rebuild everything
re: fclean all
