/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:28:27 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 16:33:56 by schaaban         ###   ########.fr       */
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
		new_path = ft_strdup((env_node)->enva, shell->mallo);
		if (change_dir(new_path, shell) == -1)
			return ;
		if (update_pwd_and_oldpwd((*my_envp), new_path, shell) == -1)
			return ;
		shell->exit_code = 0;
	}
}

void	cd_directory(t_token *head, t_env **my_envp, t_shell *shell)
{
	char	*new_pwd;
	t_env	*env_node;
	char	cwd[10000];

	if (head->next && head->next->type == DIRECTORY)
	{
		env_node = search_env((*my_envp), "PWD");
		if (env_node == NULL)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
				add_node_cd(my_envp, "PWD", cwd, shell);
			env_node = search_env((*my_envp), "PWD");
		}
		new_pwd = ft_strjoin(env_node->enva, "/", shell->mallo);
		if (env_node->enva[ft_strlen(env_node->enva) - 1] == '/')
			new_pwd = ft_strjoin(env_node->enva, head->next->token,
					shell->mallo);
		else
			new_pwd = ft_strjoin_three(env_node->enva, "/", head->next->token,
					shell);
		if (change_dir(new_pwd, shell) == -1
			|| update_pwd_and_oldpwd((*my_envp), new_pwd, shell) == -1)
			return ;
		shell->exit_code = 0;
	}
}

void	add_node_cd(t_env **my_envp, char *type, char *value, t_shell *shell)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = ft_malloc(shell->mallo, sizeof(t_env));
	new_node->type = type;
	new_node->enva = value;
	new_node->equal = true;
	new_node->next = NULL;
	new_node->all = ft_strjoin(type, "=", shell->mallo);
	new_node->all = ft_strjoin(new_node->all, value, shell->mallo);
	temp = *my_envp;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new_node;
	new_node->prev = temp;
}

void	cd_two_points(t_token *head, t_env **my_envp, t_shell *shell)
{
	t_env	*env_node;
	char	*new_path;
	int		j;
	char	cwd[1000];

	j = 0;
	if (head->next && head->next->type == TWO_POINTS)
	{
		env_node = search_env((*my_envp), "PWD");
		if (env_node == NULL)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				add_node_cd(my_envp, "PWD", cwd, shell);
			}
			env_node = search_env((*my_envp), "PWD");
		}
		j = find_last_backslash(env_node->enva);
		new_path = ft_strndup(env_node->enva, j, shell);
		if (change_dir(new_path, shell) == -1)
			return ;
		shell->exit_code = 0;
		if (update_pwd_and_oldpwd((*my_envp), new_path, shell) == -1)
			return ;
	}
}
