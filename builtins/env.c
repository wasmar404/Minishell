/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:54:01 by wasmar            #+#    #+#             */
/*   Updated: 2025/06/02 10:10:05 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*create_node_tokenn(char *str, t_env_struct *env, char *all_line,
		t_shell *shell)
{
	t_env	*new_node;

	new_node = ft_malloc(shell->mallo, sizeof(t_env));
	new_node->enva = str;
	new_node->type = env->type;
	new_node->equal = env->equal;
	new_node->all = all_line;
	new_node->printed = false;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

int	count_nodes(t_env *head)
{
	int	i;

	i = 0;
	while (head != NULL)
	{
		i++;
		head = head->next;
	}
	return (i);
}

void	env_to_linked_list_helper(t_env_struct *env)
{
	if (env->head == NULL)
	{
		env->head = env->new_node;
		env->print = env->head;
	}
	else
	{
		env->head->next = env->new_node;
		env->new_node->prev = env->head;
		env->head = env->head->next;
	}
}

t_env	*env_to_linked_list(char **envp, t_shell *shell)
{
	t_env_struct	*env;

	env = ft_malloc(shell->mallo, sizeof(t_env_struct));
	init_t_env_struct(env);
	while (envp[env->i])
	{
		env->type = NULL;
		env->j = 0;
		env->j = check_equal(envp[env->i]);
		env->equal = false;
		if (env->j != 0)
		{
			env->j++;
			env->equal = true;
			env->type = ft_strndup(envp[env->i], env->j - 1, shell);
		}
		env->new_node = create_node_tokenn(envp[env->i] + env->j, env,
				envp[env->i], shell);
		env_to_linked_list_helper(env);
		env->i++;
	}
	return (env->print);
}

char	**env_to_array(t_env *head, t_shell *shell)
{
	int		i;
	int		len;
	char	**my_envp;
	int		str_len;

	len = count_nodes(head);
	my_envp = ft_malloc(shell->mallo, (len + 1) * sizeof(char *));
	i = 0;
	if (!my_envp)
		return (NULL);
	while (head != NULL)
	{
		if(head->all)
		{
		str_len = ft_strlen(head->all);
		my_envp[i] = ft_malloc(shell->mallo, (str_len + 1) * sizeof(char));
		ft_strcpy(my_envp[i], head->all);
		i++;
		}
		head = head->next;
	}
	my_envp[i] = NULL;
	return (my_envp);
}
