/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:06:56 by schaaban          #+#    #+#             */
/*   Updated: 2025/06/02 16:21:10 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../header.h"

typedef struct s_token		t_token;
typedef struct s_shell		t_shell;
typedef struct s_quotes		t_quotes;
typedef struct s_variables	t_variables;
typedef struct s_env		t_env;
typedef struct s_dups		t_dups;
typedef struct s_exe		t_exe;

void						check_and_create_pipe(t_token *current_next,
								int *pipe_fd, int *flag, t_shell *shell);
void						init_exe_struct(t_exe *exe);
void						restore_terminal_file_descriptor(t_exe *exe);
void						builtin_and_no_pipe(t_exe *exe, t_token *current,
								t_shell *shell);
void						handle_heredoc_and_redirections_no_cmd(
								t_token *head,
								t_token *current);
void						manage_wait_status(t_exe *exe, t_shell *shell);
void						handle_fork(t_exe *exe, t_token *current,
								t_env **my_envp, t_shell *shell);
void						ft_exit(t_token *current, t_shell *shell);
void						complicated_execute(t_env **my_envp, t_token *head,
								t_shell *shell);
void						complicated_execute_helper(t_exe *exe,
								t_shell *shell);
#endif
