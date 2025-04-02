/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:28:27 by wasmar            #+#    #+#             */
/*   Updated: 2025/04/02 08:15:45 by wasmar           ###   ########.fr       */
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
			// printf("envp: %s",envp->enva);
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
	strcpy(env_node->enva, new_path);
	env_node = search_env(my_envp, "OLDPWD");
	if (env_node == NULL)
		return (-1);
	strcpy(env_node->enva, new_oldpwd);
	return (1);
}
int	find_last_backslash(char *str)
{
	int i = 0;
	// int j = 0;
	int old = 0;
	int new = 0;
	while (str[i])
	{
		if (str[i] == '/')
		{
			old = new;
			new = i;
			// j = i;
		}
		i++;
	}
	return (old);
}