/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:54:01 by wasmar            #+#    #+#             */
/*   Updated: 2025/03/22 14:08:43 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

t_env	*create_node_tokenn(char *str, char *type, bool equal, char *all_line,t_shell *shell)
{
	t_env	*new_node;

	new_node = ft_malloc(shell->mallo, sizeof(t_env));
	new_node->enva = str;
	new_node->type = type;
	new_node->equal = equal;
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
int print_listt(t_env *head)
{
	if(head == NULL)
		return 1;

    while (head != NULL)
    {
        if (head->all && head -> equal == true)                        
        {
            printf("%s\n", head->all);
        }
        head = head->next;
    }
	return 0;
}

int	check_equal(char *str)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(str);
	while (str[j] != '\0')
	{
		if (str[j] == '=')
		{
			return (j);
		}
		if (j > len)
		{
			printf("fgifdsgfvkgv");
			break ;
		}
		j++;
	}
	return (0);
}
t_env	*env_to_linked_list(char **envp,t_shell *shell)
{
	int		i;
	t_env	*head;
	t_env	*new_node;
	t_env	*print;
	char	*a;
	bool	equal;
	int		j;

	i = 0;
	head = NULL;
	a = NULL;
	
	j = 0;
	while (envp[i])
	{
		a = NULL;
		j = 0;
		j = check_equal(envp[i]);
		equal = false;
		if (j != 0)
		{
			j++;
			equal = true;
			a = ft_strndup(envp[i], j - 1,shell);
		}
		new_node = create_node_tokenn(envp[i] + j, a, equal, envp[i],shell);
		if (head == NULL)
		{
			head = new_node;
			print = head;
		}
		else
		{
			head->next = new_node;
			new_node->prev = head;
			head = head->next;
		}
		i++;
	}
	return (print);
}
char	**env_to_array(t_env *head,t_shell *shell)
{
	int	i;

	int len = count_nodes(head);                        
	char **my_envp = ft_malloc(shell->mallo,(len + 1) * sizeof(char *));
	i = 0;
	if (!my_envp)
		return (NULL);
	while (head != NULL)
	{
		int str_len = ft_strlen(head->all);               
		my_envp[i] = ft_malloc(shell->mallo,(str_len + 1) * sizeof(char));

		strcpy(my_envp[i], head->all); 
		head = head->next;
		i++;
	}
	my_envp[i] = NULL; 
	return (my_envp);
}

void	print_array(char **str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		printf("%s\n", str[j]);
		j++;
	}
	printf("\n");
}