/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:28:27 by wasmar            #+#    #+#             */
/*   Updated: 2025/04/04 16:49:31 by schaaban         ###   ########.fr       */
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

// void	cd_directory(t_token *head, t_env **my_envp, t_shell *shell)
// {
// 	char	*new_pwd;
// 	t_env	*env_node;

// 	if (head->next && head->next->type == DIRECTORY)
// 	{
// 		env_node = search_env((*my_envp), "PWD");
// 		if (env_node == NULL)
// 		{
// 			ft_putendl_fd("cd: PWD not set\n", 2);
// 			shell->exit_code = 1;
// 			return ;
// 		}
// 		new_pwd = ft_strjoin(env_node->enva, "/", shell->mallo);
// 		if (ft_strcmp(head->next->token, env_node->enva) != 0)
// 		{
// 			new_pwd = ft_strjoin(new_pwd, head->next->token, shell->mallo);
// 		}
// 		if (change_dir(new_pwd, shell) == -1)
// 			return ;
// 		if (update_pwd_and_oldpwd((*my_envp), new_pwd, shell) == -1)
// 			return ;
// 		shell->exit_code = 0;
// 	}
// }
char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3, t_shell *shell)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (!s1 || !s2 || !s3)
		return (NULL);

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);

	result = ft_malloc(shell->mallo, len1 + len2 + len3 + 1); // Corrected argument order
	if (!result)
		return (NULL);

	ft_strcpy(result, s1);
	ft_strcpy(result + len1, s2);
	ft_strcpy(result + len1 + len2, s3);
	result[len1 + len2 + len3] = '\0';

	return (result);
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
		new_pwd = ft_strjoin(env_node->enva, "/", shell->mallo);
		// if (ft_strcmp(head->next->token, env_node->enva) != 0)
		// {
		// 	new_pwd = ft_strjoin(new_pwd, head->next->token, shell->mallo);
		// }
		if (env_node->enva[ft_strlen(env_node->enva) - 1] == '/')
			new_pwd = ft_strjoin(env_node->enva, head->next->token, shell->mallo);
		else
			new_pwd = ft_strjoin_three(env_node->enva, "/", head->next->token, shell);
		if (change_dir(new_pwd, shell) == -1)
			return ;
		if (update_pwd_and_oldpwd((*my_envp), new_pwd, shell) == -1)
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
		new_path = ft_strndup(env_node->enva, j, shell);
		if (change_dir(new_path, shell) == -1)
			return ;
		shell->exit_code = 0;
		if (update_pwd_and_oldpwd((*my_envp), new_path, shell) == -1)
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
		if (update_pwd_and_oldpwd((*my_envp), env_node->enva, shell) == -1)
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
		new_path = ft_strdup((env_node)->enva, shell->mallo);
		if (change_dir(new_path, shell) == -1)
			return ;
		if (update_pwd_and_oldpwd((*my_envp), new_path, shell) == -1)
			return ;
		shell->exit_code = 0;
	}
}
