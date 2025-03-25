/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:04:03 by wasmar            #+#    #+#             */
/*   Updated: 2025/03/25 12:14:45 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

t_env	*check_if_var_exists(t_env *my_envp, char *type)
{
	while (my_envp != NULL)
	{
		if (ft_strcmp(my_envp->type, type) == 0)
		{
			return (my_envp);
		}
		my_envp = my_envp->next;
	}
	return (NULL);
}
void	reset_bool_printed(t_env *head)
{
	while (head != NULL)
	{
		head->printed = false;
		head = head->next;
	}
}
char	*ft_strdupp(char *str, int i, t_shell *shell)
{
	int		z;
	char	*array;

	z = 0;
	array = ft_malloc(shell->mallo, (i + 1) * sizeof(char));
	if (!array)
	{
		return (NULL);
	}
	while (z < i)
	{
		array[z] = str[z];
		z++;
	}
	array[z] = '\0';
	return (array);
}
void	print_env_sorted(t_env *head)
{
	t_env	*smallest_value;
	t_env	*new_head;

	while (1)
	{
		smallest_value = NULL;
		new_head = head;
		while (new_head != NULL)
		{
			if (!new_head->printed && (!smallest_value
					|| ft_strcmp(smallest_value->all, new_head->all) > 0))
			{
				smallest_value = new_head;
			}
			new_head = new_head->next;
		}
		if (!smallest_value)
		{
			break ;
		}
		if (check_equal(smallest_value->all) == 0)
		{
			printf("declare -x %s\n", smallest_value->type);
		}
		else
			printf("declare -x %s=\"%s\"\n", smallest_value->type,
				smallest_value->enva);
		smallest_value->printed = true;
	}
}

t_env	*find_tail(t_env *my_envp)
{
	while (my_envp->next != NULL)
	{
		my_envp = my_envp->next;
	}
	return (my_envp);
}
int	check_equall(t_token *head)
{
	int	i;

	i = 0;
	while (head->token[i])
	{
		if (head->token[i] == '=')
			return (i);
		i++;
	}
	return (i);
}
void	find_type(t_token *head, t_env **my_envp, t_shell *shell)
{
	int		i;
	char	*type;
	t_env	*a;
	t_env	*tail;
	int		len;
	char	*enva;
	t_env	*new_node;
	char	*all;
	char	*temp;

	head = head->next;
	while(head && head->type == WORD)
	{
		i = check_equall(head);
		type = ft_strdupp(head->token, i, shell);
		a = check_if_var_exists(*my_envp, type);
		if (a == NULL)
		{
			tail = find_tail(*my_envp);
			len = ft_strlen(head->token);
			enva = ft_strdupp(head->token + i + 1, len - (i + 1), shell);
			new_node = create_node_tokenn(enva, type, check_equal(head->token),
					head->token, shell);
			tail->next = new_node;
			new_node->next = NULL;
			new_node->prev = tail;
		}
		else
		{
			len = ft_strlen(head->token);
			enva = ft_strdupp(head->token + i + 1, len - (i + 1), shell);
			strcpy(a->enva, enva);
			a->equal = true;
			all = ft_strjoin(a->type, "=", shell->mallo);
			temp = ft_strjoin(all, a->enva, shell->mallo);
			a->all = temp; // Assign the final result to `a->all`
		}
		head = head -> next;
	}

}
void	export_main(t_env **my_envp, t_token *head, t_shell *exitcode)
{
	if (valid_identifier(head) == 0)
	{
		exitcode->exit_code = 1;
		return ;
	}
	if (head->next && head->next->type == 6)
		find_type(head, my_envp, exitcode);
	else
	{
		print_env_sorted(*my_envp);
		reset_bool_printed(*my_envp);
	}
	exitcode->exit_code = 0;
}
