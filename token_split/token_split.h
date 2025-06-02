/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:23:48 by schaaban          #+#    #+#             */
/*   Updated: 2025/06/02 16:22:10 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_SPLIT_H
# define TOKEN_SPLIT_H

# include "../header.h"

typedef struct s_token			t_token;
typedef struct s_shell			t_shell;
typedef struct s_quotes			t_quotes;
typedef struct s_variables		t_variables;
typedef struct s_env			t_env;
typedef struct s_export			t_export;
typedef struct s_ints			t_ints;
typedef struct s_env_struct		t_env_struct;
typedef struct s_token_split	t_token_split;

// token_split_helper1.c
char							*ft_strndup1(char *str, int i, t_malloc *mallo);
int								check_double_sep(char *input, int i);
int								check_single_sep(char input);
char							*ft_strndup(char *str, int i, t_shell *shell);
int								check_single_sep_quote(char input);
void							parse_non_delimiter(t_token_split *split,
									char *str, t_malloc *mallo);
void							init_token_split_struct(t_token_split *split,
									char *str);
#endif