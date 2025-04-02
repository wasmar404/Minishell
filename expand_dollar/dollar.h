/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:23:48 by schaaban          #+#    #+#             */
/*   Updated: 2025/04/02 08:15:35 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOLLAR_H
# define DOLLAR_H

# include "../header.h"
typedef struct t_token		t_token;
typedef struct t_shell		t_shell;
typedef struct t_quotes		t_quotes;
typedef struct t_variables	t_variables;
typedef struct t_env		t_env;

void						process_dolloris(t_token *head, t_shell *shell);
void						process_dolloris_helper(int *i, t_token **head,
								t_quotes *quotes, t_shell *shell);
void						initialize_variable(t_variables *var);
int							handle_empty_variable(t_token **head, char *str);
void						check_quotes_till_end(char *str, t_quotes *quotes,
								int start, int end);
char						*create_array_till_dollar(t_token *head, int index,
								t_shell *shell);
int							find_dollar_position1(char *str, int j);
int							find_end_variable(char *str, int j);
void						update_quote_status(t_quotes *quotes, char c);
char						*check_char_after_dollar_and_expand(char *str,
								int inside_quote, t_shell *shell);
void						expand_variable(t_token **head, char *str, int end,
								t_shell *shell);
void						if_expanded(t_variables *var, int *i,
								t_token **head, t_shell *shell);
char						*expand_dollar(char *str, t_env *envp,
								t_shell *shell);

#endif