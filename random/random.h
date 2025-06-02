/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:23:48 by schaaban          #+#    #+#             */
/*   Updated: 2025/06/02 16:22:01 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_H
# define RANDOM_H

# include "../header.h"

typedef struct s_token			t_token;
typedef struct s_shell			t_shell;
typedef struct s_quotes			t_quotes;
typedef struct s_variables		t_variables;
typedef struct s_env			t_env;
typedef struct s_export			t_export;
typedef struct s_ints			t_ints;
typedef struct s_env_struct		t_env_struct;
typedef struct s_remove_quotes	t_remove_quotes;

int								valid_identifier_helper(t_token *head);
int								valid_identifier(t_token *head);
int								invalid_option(t_token *head);
void							*ft_malloc(t_malloc *var, size_t size);
void							ft_free_all(t_malloc *gc);
int								is_fd_open(int fd);
void							ft_close(int fd);
void							ctrl_c(int sig);
void							main_signal(void);
void							ignore_signals(void);
void							restore_signals(void);
t_env							*search_and_find_a_type_my_envpp(t_env *envp,
									char *to_find);
int								is_alphanumeric(char c);
char							*ft_strcpy(char *dest, const char *src);
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);
void							search_and_find_a_type_my_envp(t_env **envp,
									char *to_find);
void							return_env_to_beginning(t_env **my_envp);
int								valid_identifier_helper_test(t_token *head);
#endif