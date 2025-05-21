/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:23:48 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/21 13:23:45 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "../header.h"

typedef struct t_token		t_token;
typedef struct t_shell		t_shell;
typedef struct t_quotes		t_quotes;
typedef struct t_variables	t_variables;
typedef struct t_env		t_env;
typedef struct t_export		t_export;
typedef struct t_ints		t_ints;
typedef struct t_env_struct	t_env_struct;

// input_error_handling_1.c
int							input_check(t_token *head, t_shell *exitcode);
void						ft_putendl_fd_two(char *s, char *str, int fd);
int							check_cd_command(t_token *head, t_shell *exitcode);
int							check_if_dir_after_redirections(t_token *head,
								t_shell *exitcode);
int							main_quote_check(char *str, t_shell *exitcode);

// input_error_handling_2.c
int							check_here_doc(t_token *head, t_shell *exitcode);
int							check_redirections_sequence(t_token *head,
								t_shell *exitcode);
int							check_aout_redirection(t_token *head,
								t_shell *exitcode);
int							check_sout_redirection(t_token *head,
								t_shell *exitcode);
int							check_if_file_exists(t_token *head,
								t_shell *exitcode);
// input_error_handling_3.c
int							count_redirections(t_token *head);
int							count_commands(t_token *head);
int							check_if_pipe_is_valid_helper(t_token *head,
								t_shell *shell, int flag);
int							check_if_pipe_is_valid(t_token *head,
								t_shell *exitcode);
int							check_command(char *array, char **envp,
								t_shell *exitcode);
int							check_command_helper(char *array,
								t_shell *exitcode);
#endif