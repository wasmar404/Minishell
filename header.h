/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:01:29 by schaaban          #+#    #+#             */
/*   Updated: 2025/02/05 15:22:35 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include "get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdlib.h>
# include <sys/wait.h>
#include <errno.h>
# include <unistd.h>
#include <sys/stat.h>
#include <signal.h>

# define RESET "\033[0m"
# define BOLD_CYAN "\033[1;36m"
typedef enum token_type
{
	COMMAND,
	PIPE,
	SOUTPUT_REDIRECTION,
	AOUTPUT_REDIRECTION,
	SINPUT_REDIRECTION,
	HERE_DOC,
	WORD,
	TILDE,
	MINUS,
	TWO_POINTS,
	DIRECTORY
}					token_type;
typedef enum dollar_type
{
	QUOTES,
	CHARACTERS,
	NUMBERS,
	STRING
}	dollar_type;

typedef struct t_token
{
	char			*token;
	int				type;
	bool			built_in_or_not;
	int node_count;
	struct t_token	*next;
	struct t_token	*prev;
}					t_token;

typedef struct t_env
{
	char			*enva;
	char			*type;
	char			*all;
	bool			equal;
	bool			printed;
	struct t_env	*next;
	struct t_env	*prev;

}					t_env;
// globals.h
extern long long  exit_code;
void heredoc_dup(t_token *head);
int main_error1(t_token *head);
void heredoc_dup(t_token *head);
void super_complicated_handle_dups(t_token *head,int *pipefd, int input_fd,int flag);
int					check_double_sep(char *input, int i);
int					check_single_sep(char input);
char				*ft_strndup(char *str, int i);
int					delimeter_check(char **tokens, int *token, char *str,
						int *i);
void				check_non_delimeter(char **tokens, int *token, char *str,
						int *i);
int					token_count(char *input);
char				**token_split(char *str);
void				single_sep_case(int *count, int *i, int *in_token,
						char *input);
void				check_quotes(char *input, int *i, int *count,
						int *in_token);
void				token_count_helper(char *input, int *i, int *count,
						int *in_token);
int					ft_strcmp(char *str1, char *str2);
void				print_list(t_token *head);
t_token				*input_to_linked_list(char **input, char **envp);
int					count_nodes(t_env *head);
int					ft_strlenn(char *input);
t_env				*create_node_tokenn(char *str, char *type, bool equal,
						char *all_line);
int					count_nodes(t_env *head);
int				print_listt(t_env *head);
int					check_equal(char *str);
t_env				*env_to_linked_list(char **envp);
char				**env_to_array(t_env *head);
void				print_array(char **str);
int					check_n(t_token *head);
int					delimeter_check_echo(t_token *head);
int					check_dollar(t_token *head);
t_env				*check_in_envp(t_env *head, char *a);
int				echo_main(t_token *head);
void				complicated_execute(t_env **my_env, t_token *head,
						char **my_envp);
int	check_dollar1(t_token *head);
t_token				*create_node_token(char *str, int i, bool built_in_or_not);
bool				built_in_or_not(char *cmd);
void				find_the_word_path_in_envp(char ***envp);
void				free_array(char **array);
int					ft_strcmp(char *str1, char *str2);
char				*find_path_of_cmd_helper(char *command);
char				*find_path_of_cmd(char *command, char **envp);
token_type			check_delimeter1(char *splitted_token);
token_type			check_delimeter2(char *splitted_token);
t_token				*input_to_linked_list(char **input, char **envp);
void				run_command(t_token *head, char **current_command,
						char **envp, t_env *my_envp, int *pipefd, int input_fd);
int					pipe_count(t_token *head);
void				heredoc(char *str, int fd);
void				run_command_helper(t_token *head, char **envp,
						t_env **my_envp, int *pipefd, int input_fd,
						char **current_command,int flag);
void				main_helper(char *input, char **envp, t_env **env_linked);
void				check_back_and_front(t_token *head_back,
						t_token **current_input, t_token **current_output,
						t_token *current);
void				dups1(t_token *current_input, t_token *current_output,
						int *pipefd);
void				dups2(t_token *current_input, t_token *current_output,
						int input_fd,t_token *head);
void				main_cd(t_token *head, t_env **my_envp);
int				main_pwd(void);
void				export_main(t_env **my_envp, t_token *head);
int					check_equal(char *str);
void				main_unset1(t_env **my_envp, char *var_name);
void				find_var_name(t_env **my_envp, char *var_name);
int					valid_identifier(t_token *head);
int					invalid_option(t_token *head);
token_type			check_delimeter(char *splitted_token, char **envp);
token_type			check_delimeter3(char *splitted_token, char **envp);

char				*return_value_of_envp_type(t_env *envp_linked,
						char *search_for);
token_type			check_if_heredoc_aoutput_minus_tilde(char *input);
token_type			check_if_pipe_soutput_sinput(char *input);
token_type			check_input_type(char *input, char **envp,t_token *head);
int					check_if_cmd(char *input, char **envp,t_token *head);
token_type			check_if_twopoints_dir_cmd_word(char *input, char **envp,t_token *head);
void				run_built_ins(t_token *head, t_env **my_envp, int *pipefd,
						int input_fd, int flag,int flag2);
void				input_to_linked_list_h(t_token **head, t_token *new);
t_token				*create_node_token(char *str, int i, bool built_in_or_not);
bool				built_in_or_not(char *cmd);
t_token				*generate_tokenn(t_env *envp_linked, char **splitted_input,
						char **envp, int i);
t_token				*input_to_linked_listt(t_env *envp_linked,
						char **splitted_input, char **envp);
int					find_quotes_end(char *str, int i, int flag);
char				*new_string(char *str, int i, int j);
void				quotes_check_remove(t_token **head, t_env *envp);
void				search_and_find_a_type_my_envp(t_env **envp, char *to_find);
int					calculate_len(t_env *enva, t_token **head, char *find);
void				update_token_in_list(char *new, t_token **head);
char				*fill_array(int len, int start, int end, t_token **head,
						t_env *enva);
int					process_token(t_token **head, t_env *envp_linked);
void				update_token_linked_list(t_token **head,
						t_env *envp_linked);
int find_end_of_quotes(char *str, char quote,int i);
void remove_quotes_and_replace(t_token **head,int i);
void remove_quotes_main(t_token **head);
void main_dollar(t_token **head,t_env *envp);
char * check_dollar_plus1_char(char **str);
char *dollar_main_char(char *str);
t_env	*search_and_find_a_type_my_envpp(t_env *envp, char *to_find);
void expand_dollar1(t_token **head,t_env *envp_linked);
int check_if_null(char *input);
void remove_empty_nodes(t_token **head);
char *check_access_for_files(t_token *head);
char	*find_path_of_cmd(char *command, char **envp);
int input_check(t_token *head,char **array,char **envp);
int  main_quote_check(char *str);
void check_quotes_status_and_update(int *inside_quote, int *d_start,int *d_end, int *s_start,int *s_end , char c);
void	ft_putendl_fd_two(char *s,char *str, int fd);
void add_type(t_token **head,char **envp);
void replace_exit_code(t_token *head);
void exit_command(t_token *head);
int check_command(char *array,char **envp);
void ctrl_c(int sig);
void main_signal();
#endif