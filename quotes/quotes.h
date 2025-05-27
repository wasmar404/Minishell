/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:23:48 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/27 10:21:23 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

# include "../header.h"

typedef struct t_token			t_token;
typedef struct t_shell			t_shell;
typedef struct t_quotes			t_quotes;
typedef struct t_variables		t_variables;
typedef struct t_env			t_env;
typedef struct t_export			t_export;
typedef struct t_ints			t_ints;
typedef struct t_env_struct		t_env_struct;
typedef struct t_remove_quotes	t_remove_quotes;

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