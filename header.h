/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:01:29 by schaaban          #+#    #+#             */
/*   Updated: 2024/12/20 13:35:55 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADEAR_H
# define HEADER_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"

#define RESET "\033[0m"
#define BOLD_CYAN "\033[1;36m"
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

typedef struct t_token
{
	char			*token;
	int				type;
	bool			built_in_or_not;
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
void				print_listt(t_env *head);
int					check_equal(char *str);
t_env				*env_to_linked_list(char **envp);
char				**env_to_array(t_env *head);
void				print_array(char **str);
int					check_n(t_token *head);
int					delimeter_check_echo(t_token *head);
int					check_dollar(t_token *head);
t_env				*check_in_envp(t_env *head, char *a);
void				echo_main(t_token *head, t_env *envp);
void				complicated_execute(t_env **my_env, t_token *head,
						char **my_envp);
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
void	run_command(t_token *head, char **current_command, char **envp,
		t_env *my_envp, int *pipefd,int input_fd);
int pipe_count(t_token *head);
void heredoc(char *str,int fd);
void run_command_helper(t_token *head,char **envp, t_env **my_envp,int *pipefd,int input_fd,char **current_command);
void	main_helper(char *input, char **envp,t_env **env_linked);
void check_back_and_front(t_token *head_back,t_token **current_input,t_token **current_output,t_token *current);
void dups1(t_token *current_input,t_token *current_output,int *pipefd);
void dups2(t_token *current_input,t_token *current_output,int input_fd);
void main_cd(t_token *head, t_env **my_envp);
void main_pwd();
void run_built_ins1(t_token *head,char **envp, t_env **my_envp,int *pipefd,int input_fd,char **current_command);
void export_main(t_env **my_envp,t_token *head);
int	check_equal(char *str);
void main_unset1(t_env **my_envp ,char *var_name);
void find_var_name(t_env **my_envp,char *var_name);
int valid_identifier(t_token *head);
int invalid_option(t_token *head);
token_type	check_delimeter(char *splitted_token, char **envp);
token_type	check_delimeter3(char *splitted_token, char **envp);

char *return_value_of_envp_type(t_env *envp_linked,char *search_for);
token_type	check_if_heredoc_aoutput_minus_tilde(char *input);
token_type	check_if_pipe_soutput_sinput(char *input);
token_type	check_input_type(char *input, char **envp,char **splitted_input,int i);
int check_if_cmd(char *input, char **envp,char **splitted_input,int i);
token_type	check_if_twopoints_dir_cmd_word(char *input, char **envp,char **splitted_input,int i);
token_type	check_input_type(char *input, char **envp,char **splitted_input,int i);
#endif