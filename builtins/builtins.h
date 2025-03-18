/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:23:48 by schaaban          #+#    #+#             */
/*   Updated: 2025/03/18 07:35:18 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#include "../header.h"
typedef struct t_token t_token;
typedef struct t_shell t_shell;
typedef struct t_quotes t_quotes;
typedef struct t_variables t_variables;
typedef struct t_env t_env;

//cd.c
void	main_cd(t_token *head, t_env **my_envp, t_shell *shell);
void	cd(t_token *head, t_env **my_envp, t_shell *shell);
void	cd_directory(t_token *head, t_env **my_envp, t_shell *shell);
void	cd_two_points(t_token *head, t_env **my_envp, t_shell *shell);
void	cd_minus(t_token *head, t_env **my_envp, t_shell *shell);
void	cd_tilde(t_token *head, t_env **my_envp, t_shell *shell);

//cd_helper.c
int	change_dir(char *tochange, t_shell *shell);
t_env	*search_env(t_env *envp, char *to_find);
int	update_pwd_and_oldpwd(t_env *my_envp, char *new_path);
int	find_last_backslash(char *str);


#endif