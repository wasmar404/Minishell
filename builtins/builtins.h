/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:23:48 by schaaban          #+#    #+#             */
/*   Updated: 2025/03/17 20:46:19 by wasmar           ###   ########.fr       */
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

int change_dir(char *tochange,t_shell *shell);
t_env *search_env(t_env *envp,char *to_find);

int 	update_pwd_and_oldpwd(t_env *my_envp, char *new_path);

void cd(t_token *head, t_env **my_envp,t_shell *shell);
void main_cd(t_token *head, t_env **my_envp, t_shell *shell);
void	cd_DIRECTORY(t_token *head, t_env **my_envp, t_shell *shell);
int	find_last_backslash(char *str);
void	cd_TWO_POINTS(t_token *head, t_env **my_envp, t_shell *shell);

#endif