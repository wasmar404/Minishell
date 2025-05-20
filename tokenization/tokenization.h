/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:23:48 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/20 08:07:56 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "../header.h"

typedef struct t_token		t_token;
typedef struct t_shell		t_shell;
typedef struct t_quotes		t_quotes;
typedef struct t_variables	t_variables;
typedef struct t_env		t_env;

t_token						*parse_input_to_tokens(char **splitted_input,
								t_shell *shell);
void						add_type(t_token *head, char **envp,
								t_shell *shell);
t_token						*generate_token(char **splitted_input, int i,
								t_shell *shell);
token_type					check_input_type(char *input, char **envp,
								t_token *head, t_shell *shell);
token_type					check_if_heredoc_aoutput_minus_tilde(char *input);
token_type					check_if_pipe_soutput_sinput(char *input);
token_type					check_if_twopoints_dir_cmd_word(char *input,
								char **envp, t_token *head, t_shell *shell);
int							count_ttoken_nodes(t_token *head);
int							check_if_cmd(char *input, char **envp,
								t_token *head, t_shell *shell);
t_token						*create_node_token(char *str, int i,
								bool built_in_or_not, t_shell *shell);
char						*new_string(char *str, int i, int j,
								t_shell *shell);
void						remove_quotes_and_replace(t_token **head, int start,
								t_shell *shell);
int							find_end_of_quotes(char *str, char quote,
								int start);
bool						built_in_or_not(char *cmd);
void						find_the_word_path_in_envp(char ***envp);
int							ft_strcmp(char *str1, char *str2);
char						*find_path_of_cmd_helper(char *command);

char						*find_path_of_cmd_main_helper(char **all_path,
								char *cmd_path, t_shell *shell, char *command);
char						*find_path_of_cmd(char *command, char **envp,
								t_shell *shell);
token_type					check_delimeter1(char *splitted_token);
token_type					check_delimeter2(char *splitted_token);
token_type					check_delimeter3(char *splitted_token, char **env,
								t_shell *shell);
token_type					check_delimeter(char *splitted_token, char **envp,
								t_shell *shelll);
void						append_token_node(t_token **head, t_token *new);
int							remove_node(t_token **head, t_token *current);
void						remove_empty_nodes(t_token **head);
#endif