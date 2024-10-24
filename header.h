/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:01:29 by schaaban          #+#    #+#             */
/*   Updated: 2024/10/24 13:35:31 by wasmar           ###   ########.fr       */
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
void				main_helper(char *input, char **envp);
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
void				complicated_execute(t_env *my_env, t_token *head,
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
token_type			check_delimeter3(char *splitted_token, char **envp);
token_type			check_delimeter(char *splitted_token, char **envp);
t_token				*input_to_linked_list(char **input, char **envp);
#endif