/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:14:54 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/29 16:40:37 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUPS_H
# define DUPS_H

# include "../header.h"

typedef struct t_token		t_token;
typedef struct t_shell		t_shell;
typedef struct t_quotes		t_quotes;
typedef struct t_variables	t_variables;
typedef struct t_env		t_env;
typedef struct t_dups		t_dups;
typedef struct t_exe		t_exe;

void						check_front_heredoc(t_token *head, t_env *envp,
								t_shell *shell);
void						check_front_sinput_redirection(t_token *head,
								t_shell *shell);
int							check_front_out_redirection_and_pipe(
								t_token **current_output,
								t_token *head, int *flag);
int							if__check_front_out_redirection_pipe(
								t_token **current_output,
								t_token *head, int *flag);
int							check_and_create_file_soutput_redirectio(
								t_token *head,
								int *fd, int *dev_null);
int							check_and_create_file_aoutput_redirection(
								t_token *head,
								int *fd, int *dev_null);
void						check_back_sinput_redirection(t_token *head,
								t_shell *shell);
void						init_dups_struct(t_dups *dups, t_token *head);
void						super_complicated_handle_dups(t_token *head,
								t_exe *exe, t_shell *shell, int test);
int							check_and_create_file(t_token *head);
void						check_front(t_dups *dups, t_shell *exitcode);
void						check_back(t_token *head, t_dups *dups,
								t_shell *exitcode);
void						dups2(t_token *current_input, int input_fd);
void						dups1(t_dups *dups, int *pipefd);
int							check_front_out_redirection_and_pipe2(
								t_token **current_output,
								t_token *head, int *flag);
int							check_front_helper42(t_dups *dups,
								t_shell *exitcode);

#endif