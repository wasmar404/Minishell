/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:29:57 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/20 16:34:01 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "builtins.h"

char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3,
		t_shell *shell)
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
	result = ft_malloc(shell->mallo, len1 + len2 + len3 + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcpy(result + len1, s2);
	ft_strcpy(result + len1 + len2, s3);
	result[len1 + len2 + len3] = '\0';
	return (result);
}

char	*cd_tilde_helper(void)
{
	char	cwd[1000];
	int		i;
	int		slash_count;
	char	*result;

	i = 0;
	slash_count = 0;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	while (cwd[i] != '\0')
	{
		if (cwd[i] == '/')
			slash_count++;
		if (slash_count == 3)
			break ;
		i++;
	}
	result = malloc(i + 1);
	if (!result)
		return (NULL);
	strncpy(result, cwd, i);
	result[i] = '\0';
	return (result);
}

void	cd_tilde(t_token *head, t_env **my_envp, t_shell *shell)
{
	t_env	*env_node;
	char	*new_path;
	char	*s;

	env_node = NULL;
	if (head->next && head->next->type == TILDE)
	{
		env_node = search_env((*my_envp), "HOME");
		if (env_node == NULL)
		{
			s = cd_tilde_helper();
			add_node_cd(my_envp, "HOME", s, shell);
			env_node = search_env((*my_envp), "HOME");
		}
		new_path = ft_strdup((env_node)->enva, shell->mallo);
		if (change_dir(new_path, shell) == -1)
			return ;
		if (update_pwd_and_oldpwd((*my_envp), new_path, shell) == -1)
			return ;
		shell->exit_code = 0;
	}
}

void	cd_minus(t_token *head, t_env **my_envp, t_shell *shell)
{
	t_env	*env_node;

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
