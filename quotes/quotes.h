/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:23:48 by schaaban          #+#    #+#             */
/*   Updated: 2025/06/02 16:21:52 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

# include "../header.h"

typedef struct s_token			t_token;
typedef struct s_shell			t_shell;
typedef struct s_quotes			t_quotes;
typedef struct s_variables		t_variables;
typedef struct s_env			t_env;
typedef struct s_export			t_export;
typedef struct s_ints			t_ints;
typedef struct s_env_struct		t_env_struct;
typedef struct s_remove_quotes	t_rq;

void							init_remove_quotes_struct(t_rq *quotes);
int								do_not_remove_quotes_for_heredoc_delimiter(
									t_token *head);
int								double_quotes_remove(t_token *head,
									t_shell *shell, t_rq *quotes);
int								single_quotes_remove(t_token *head,
									t_shell *shell, t_rq *quotes);
void							remove_quotes_main(t_token *head,
									t_shell *shell);

int								do_not_remove_quotes_for_heredoc_delimiter(
									t_token *head);

#endif