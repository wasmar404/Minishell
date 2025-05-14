/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:04:03 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/13 10:32:56 by schaaban         ###   ########.fr       */
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
			break ;
		if (check_equal(smallest_value->all) == 0)
			printf("declare -x %s\n", smallest_value->type);
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


void	init_t_export(t_export *exp)
{
	exp->i = 0;
	exp->type = NULL;
	exp->a = NULL;
	exp->tail = NULL;
	exp->len = 0;
	exp->enva = NULL;
	exp->new_node = NULL;
	exp->all = NULL;
	exp->temp = NULL;
	exp->env = NULL;
}

void	find_type_helper(t_export *export, t_token *head, t_env **my_envp,
		t_shell *shell)
{
	export->env->equal = check_equal(head->token);
	export->env->type = ft_malloc(shell->mallo, ft_strlen(export->type) + 1);
	ft_strcpy(export->env->type, export->type);
	export->tail = find_tail(*my_envp);
	export->len = ft_strlen(head->token);
	export->enva = ft_strdupp(head->token + export->i + 1, export->len
			- (export->i + 1), shell);
	export->new_node = create_node_tokenn(export->enva, export->env,
			head->token, shell);
	export->tail->next = export->new_node;
	export->new_node->next = NULL;
	export->new_node->prev = export->tail;
}
void	find_type_helper_1(t_export *export, t_token *head, t_shell *shell)
{
	export->len = ft_strlen(head->token);
	export->enva = ft_strdupp(head->token + export->i + 1, export->len
			- (export->i + 1), shell);
	ft_strcpy(export->a->enva, export->enva);
	export->a->equal = true;
	export->all = ft_strjoin(export->a->type, "=", shell->mallo);
	export->temp = ft_strjoin(export->all, export->a->enva, shell->mallo);
	export->a->all = export->temp;
}
void	find_type(t_token *head, t_env **my_envp, t_shell *shell)
{
	t_export	*export;

	export = ft_malloc(shell->mallo, sizeof(t_export));
	head = head->next;
	export->env = ft_malloc(shell->mallo, sizeof(t_env_struct));
	while (head && head->type == WORD)
	{
		export->i = check_equall(head);
		export->type = ft_strdupp(head->token, export->i, shell);
		export->a = check_if_var_exists(*my_envp, export->type);
		if (export->a == NULL)
		{
			find_type_helper(export, head, my_envp, shell);
		}
		else
		{
			find_type_helper_1(export, head, shell);
		}
		head = head->next;
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
