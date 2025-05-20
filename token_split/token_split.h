/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:23:48 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/20 10:30:15 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_SPLIT_H
# define TOKEN_SPLIT_H

# include "../header.h"

typedef struct t_token		t_token;
typedef struct t_shell		t_shell;
typedef struct t_quotes		t_quotes;
typedef struct t_variables	t_variables;
typedef struct t_env		t_env;
typedef struct t_export		t_export;
typedef struct t_ints		t_ints;
typedef struct t_env_struct	t_env_struct;

// token_split_helper1.c
char						*ft_strndup1(char *str, int i, t_malloc *mallo);
int							check_double_sep(char *input, int i);
int							check_single_sep(char input);
char						*ft_strndup(char *str, int i, t_shell *shell);
int							check_single_sep_quote(char input);

#endif