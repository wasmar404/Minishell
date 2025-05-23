/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:23:48 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/23 11:40:43 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../header.h"

typedef struct t_token		t_token;
typedef struct t_shell		t_shell;
typedef struct t_quotes		t_quotes;
typedef struct t_variables	t_variables;
typedef struct t_env		t_env;
typedef struct t_export		t_export;
typedef struct t_ints		t_ints;
typedef struct t_env_struct	t_env_struct;
// main_helper_1.c
void						init_shell_struct(t_shell *shell, char **envp);
void						init_mallo_struct(t_malloc **mallo, t_shell *shell);

int							check_if_null(char *input);
void						print_list(t_token *head);
int							pipe_count_array(char **str);
// main_helper_2.c
int							pipe_count(t_token *head);
char						**array_complicated_execute(t_token *head,
								t_shell *shell);
int							count_tokens_for_exec_array(t_token *head);
void						here_doc_first(char *s, int fd);
void						heredoc_dup(t_token *head);
// main_helper_3.c
void						s_out_redirection(t_token *head);
void						a_out_redirection(t_token *head);
int							command_exists(t_token *head);
void						change_value_in_envp(t_env *my_envp,
								char *new_value, t_shell *shell);
void						add_shell_level(t_env **my_envp, t_token *head,
								char ***envp, t_shell *shelll);
// main_helper_4.c
int							find_var_name_return(t_env *my_envp,
								char *var_name);

void						run_built_ins_helper(t_token *head, t_env **my_envp,
								t_shell *exitcode);
bool						find_var_name_first(t_env **my_envp,
								char *var_name);
void						run_built_ins_unset(t_token *head, t_shell *shell,
								t_token **tokenn);
void						run_built_ins(t_token *head, int flag, t_exe *exe,
								t_shell *shell);
// main_helper_5.c
void						heredoc(char *str, int fd, t_shell *exitcode);
void						write_two(int fd, char *input);
void						run_command_helper(t_token *head, t_shell *shell,
								t_exe *exe);
int							path_exists(char **envp);
void						external_commands(t_token *head, t_exe *exe,
								char **current_command, t_shell *exitcode);
// main_helper_6.c
void						main_heredoc_helper(t_token *head, t_shell *shell,
								int *i);
void						main_heredoc(t_token *head, t_shell *shell);
void						delete_temp_files(t_shell *shell);

// main
int							main_helper_helper(char *input, t_shell *shell,
								char ***splitted_input, t_malloc *mallo);
void						main_helper(char *input, t_shell *shell,
								t_malloc *mallo);

#endif