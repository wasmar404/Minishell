/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:28:27 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 16:08:18 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	change_dir(char *tochange, t_shell *shell)
{
	if (chdir(tochange) == -1)
	{
		shell->exit_code = 1;
		return (-1);
	}
	return (1);
}

t_env	*search_env(t_env *envp, char *to_find)
{
	while ((envp) != NULL)
	{
		if (ft_strcmp(to_find, (envp)->type) == 0)
		{
			return (envp);
		}
		(envp) = (envp)->next;
	}
	return (NULL);
}

int	update_pwd_and_oldpwd(t_env *my_envp, char *new_path, t_shell *shell)
{
	t_env	*env_node;
	char	*new_oldpwd;

	new_oldpwd = NULL;
	env_node = NULL;
	env_node = search_env(my_envp, "PWD");
	if (env_node == NULL)
		return (-1);
	new_oldpwd = ft_strdup(env_node->enva, shell->mallo);
	env_node->enva = new_path;
	env_node->all = ft_strjoin(env_node->type, "=", shell->mallo);
	env_node->all = ft_strjoin(env_node->all, env_node->enva, shell->mallo);
	env_node = search_env(my_envp, "OLDPWD");
	if (env_node == NULL)
		return (-1);
	env_node->enva = new_oldpwd;
	env_node->all = ft_strjoin(env_node->type, "=", shell->mallo);
	env_node->all = ft_strjoin(env_node->all, env_node->enva, shell->mallo);
	return (1);
}

int	find_last_backslash(char *str)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	while (str[i])
	{
		if (str[i] == '/' && str[i + 1] != '\0')
			last = i;
		i++;
	}
	return (last);
}
