# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LIBS = -lreadline -Llibft -lft  # Link to the libft library (-lft) and readline

# Files
SRC = $(wildcard *.c)  # Wildcard to include all .c files in the current directory
OBJ = $(SRC:.c=.o)
EXEC = minishell

# Rules
all: $(EXEC)

$(EXEC): $(OBJ) libft/libft.a  # Ensure libft is built before linking
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) $(LIBS)

libft/libft.a:  # Build libft if it doesn't exist or needs to be updated
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C libft clean  # Clean libft object files as well

fclean: clean
	rm -f $(EXEC)
	make -C libft fclean  # Clean libft executables as well

re: fclean all  # Rebuild everything
