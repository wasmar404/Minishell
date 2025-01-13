/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:54:01 by wasmar            #+#    #+#             */
/*   Updated: 2025/01/13 15:42:11 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

t_env	*create_node_tokenn(char *str, char *type, bool equal, char *all_line)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
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
void print_listt(t_env *head)
{
    while (head != NULL)
    {
        if (head->all && head -> equal == true)                        
        {
            printf("%s\n", head->all);
        }
        head = head->next;
    }
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
t_env	*env_to_linked_list(char **envp)
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
			a = ft_strndup(envp[i], j - 1);
		}
		new_node = create_node_tokenn(envp[i] + j, a, equal, envp[i]);
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
char	**env_to_array(t_env *head)
{
	int	i;

	int len = count_nodes(head);                        
		// Number of nodes in the list
	char **my_envp = malloc((len + 1) * sizeof(char *));
		// Allocate for 'len' strings + NULL terminator
	i = 0;
	if (!my_envp)
		return (NULL); // Check malloc success
	while (head != NULL)
	{
		int str_len = ft_strlen(head->all);               
			// Length of current string
		my_envp[i] = malloc((str_len + 1) * sizeof(char));
			// Allocate space for the string + '\0'
		if (!my_envp[i]) // Check malloc success
		{
			// Free all previously allocated memory in case of error
			while (i-- > 0)
				free(my_envp[i]);
			free(my_envp);
			return (NULL);
		}
		strcpy(my_envp[i], head->all); // Copy the string content
		head = head->next;
		i++;
	}
	my_envp[i] = NULL; // Null-terminate the array
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