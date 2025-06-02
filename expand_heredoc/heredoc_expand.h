/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:23:48 by schaaban          #+#    #+#             */
/*   Updated: 2025/06/02 16:21:30 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_EXPAND_H
# define HEREDOC_EXPAND_H

# include "../header.h"

typedef struct s_token		t_token;
typedef struct s_shell		t_shell;
typedef struct s_quotes		t_quotes;
typedef struct s_variables	t_variables;
typedef struct s_env		t_env;
typedef struct s_export		t_export;
typedef struct s_ints		t_ints;
typedef struct s_env_struct	t_env_struct;

// heredoc_expand_helper1.c
void						expand_and_replace_heredoc_helper1(char **mainstr,
								char *str, char *s);
void						expand_and_replace_heredoc(char **mainstr,
								char *str, int end, t_shell *shell);
char						*create_array_till_dollar_h(char *input, int index,
								t_shell *shell);
char						*check_char_after_dollar_and_expand1(char *str,
								t_env *envp, t_shell *exitcode);
int							check_if_quotes_exit(char *input);
// heredoc_expand_helper2.c
int							handle_double_quotes(char **str, int *i,
								t_shell *shell);
int							handle_single_quotes(char **str, int *i,
								t_shell *shell);
void						remove_quotes_main_heredoc(char **str,
								t_shell *shell);
// heredoc_expand.c
void						process_dolloris_helper_h(int *i, char **input,
								char **str, t_shell *shell);
void						process_dolloris_heredoc(char **input,
								t_shell *exitcode);
int							find_end_of_quotes_h(char *str, char quote,
								int start);
void						remove_quotes_and_replace_h(char **str, int start,
								t_shell *shell);

#endif