CC = gcc
CFLAGS = -g

NAME = minishell

LIBS = -lreadline -Llibft -lft

OBJDIR = obj

SRC = builtins/echo.c \
      builtins/echo_helper.c \
      builtins/env.c \
      builtins/env_helper.c\
      error_handling.c \
      builtins/exit.c \
      builtins/main_exit.c\
      builtins/export.c \
      builtins/main_export.c \
      builtins/export_helper.c \
      builtins/exit_helper.c \
      free.c \
      expand_heredoc/heredoc_expand.c \
      expand_heredoc/heredoc_expand_helper1.c \
      expand_heredoc/heredoc_expand_helper2.c \
      error/input_error_handling.c \
      error/input_error_handling_1.c \
      error/input_error_handling_2.c \
      error/input_error_handling_3.c \
      main/main.c \
      main/main_helper_1.c\
      main/main_helper_2.c\
      main/main_helper_3.c\
      main/main_helper_4.c\
      main/main_helper_5.c\
      main/main_helper_6.c\
      builtins/pwd.c \
      quotes.c \
      signals.c \
      token_split/token_split.c \
      token_split/token_split_helper1.c \
      token_split/token_split_helper2.c \
      tokenization/tokenization.c \
      tokenization/delimeter_check.c\
      tokenization/main_tokenization.c\
      tokenization/token_type.c\
      tokenization/tokenization_helper.c\
      builtins/unset.c \
      tokenization/updated_tokenization.c \
      utils_1.c \
      utils_2.c \
      builtins/cd_helper.c \
      builtins/cd.c \
      builtins/cd1.c\
      dups/dups.c \
      dups/dups_helper.c \
      dups/dups_helper1.c \
      execution/execution1.c \
      execution/execution2.c \
      expand_dollar/dollar.c \
      expand_dollar/dollar1.c \
      expand_dollar/dollar2.c \
      expand_dollar/dollar3.c

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

libft/libft.a:
	make -C libft

clean:
	rm -rf $(OBJDIR)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all
