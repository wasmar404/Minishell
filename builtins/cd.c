/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:28:27 by wasmar            #+#    #+#             */
/*   Updated: 2025/03/18 07:34:02 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "builtins.h"

void	main_cd(t_token *head, t_env **my_envp, t_shell *shell)
{
	if (!my_envp || !head)
	{
		shell->exit_code = 1;
		return ;
	}
	if (head && head->next && head->next->next
		&& head->next->next->type == WORD)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		shell->exit_code = 1;
		return ;
	}
	cd(head, my_envp, shell);
	cd_directory(head, my_envp, shell);
	cd_two_points(head, my_envp, shell);
	cd_minus(head, my_envp, shell);
	cd_tilde(head, my_envp, shell);
}

void	cd(t_token *head, t_env **my_envp, t_shell *shell)
{
	char	*new_path;
	t_env	*env_node;

	env_node = NULL;
	if (!(head->next))
	{
		env_node = search_env((*my_envp), "HOME");
		if (env_node == NULL)
		{
			ft_putendl_fd("cd: HOME not set\n", 2);
			shell->exit_code = 1;
			return ;
		}
		new_path = strdup((env_node)->enva);
		if (change_dir(new_path, shell) == -1)
			return ;
		if (update_pwd_and_oldpwd((*my_envp), new_path) == -1)
			return ;
		free(new_path);
		shell->exit_code = 0;
	}
}

void	cd_directory(t_token *head, t_env **my_envp, t_shell *shell)
{
	char	*new_pwd;
	t_env	*env_node;

	if (head->next && head->next->type == DIRECTORY)
	{
		env_node = search_env((*my_envp), "PWD");
		if (env_node == NULL)
		{
			ft_putendl_fd("cd: PWD not set\n", 2);
			shell->exit_code = 1;
			return ;
		}
		new_pwd = ft_strjoin(env_node->enva, "/");
		new_pwd = ft_strjoin(new_pwd, head->next->token);
		if (change_dir(new_pwd, shell) == -1)
			return ;
		if (update_pwd_and_oldpwd((*my_envp), new_pwd) == -1)
			return ;
		shell->exit_code = 0;
	}
}

void	cd_two_points(t_token *head, t_env **my_envp, t_shell *shell)
{
	t_env	*env_node;
	char	*new_path;
	char	*new_old;
	int		j;

	j = 0;
	if (head->next && head->next->type == TWO_POINTS)
	{
		env_node = search_env((*my_envp), "PWD");
		if (env_node == NULL)
		{
			ft_putendl_fd("cd: PWD not set\n", 2);
			shell->exit_code = 1;
			return ;
		}
		j = find_last_backslash(env_node->enva);
		new_path = ft_strndup(env_node->enva, j);
		if (change_dir(new_path, shell) == -1)
			return ;
		shell->exit_code = 0;
		if (update_pwd_and_oldpwd((*my_envp), new_path) == -1)
			return ;
	}
}

void	cd_minus(t_token *head, t_env **my_envp, t_shell *shell)
{
	char	*oldpwd;
	t_env	*env_node;
	char	*new_oldpwd;

	if (head->next && head->next->type == MINUS)
	{
		env_node = search_env((*my_envp), "OLDPWD");
		if (env_node == NULL)
		{
			ft_putendl_fd("cd: OLDPWD not set\n", 2);
			shell->exit_code = 1;
			return ;
		}
		if (change_dir(env_node->enva, shell) == -1)
			return ;
		if (update_pwd_and_oldpwd((*my_envp), env_node->enva) == -1)
			return ;
		shell->exit_code = 0;
	}
}

void	cd_tilde(t_token *head, t_env **my_envp, t_shell *shell)
{
	t_env	*env_node;
	char	*new_path;

	env_node = NULL;
	if (head->next && head->next->type == TILDE)
	{
		env_node = search_env((*my_envp), "HOME");
		if (env_node == NULL)
		{
			ft_putendl_fd("cd: HOME not set\n", 2);
			shell->exit_code = 1;
			return ;
		}
		new_path = strdup((env_node)->enva);
		if (change_dir(new_path, shell) == -1)
			return ;
		if (update_pwd_and_oldpwd((*my_envp), new_path) == -1)
			return ;
		free(new_path);
		shell->exit_code = 0;
	}
}
