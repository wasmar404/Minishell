/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:16:26 by wasmar            #+#    #+#             */
/*   Updated: 2025/01/13 17:02:01 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

// t_token	*create_node_token(char *str, int i, bool built_in_or_not)
// {
// 	t_token	*new_node;

// 	new_node = malloc(sizeof(t_token));
// 	new_node->token = str;
// 	new_node->built_in_or_not = built_in_or_not;
// 	new_node->type = i;
// 	new_node->next = NULL;
// 	new_node->prev = NULL;
// 	return (new_node);
// }
bool	built_in_or_not(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	else
		return (false);
}
void	find_the_word_path_in_envp(char ***envp)
{
	while (**envp != NULL)
	{
		if (ft_strnstr(**envp, "PATH=", 5) != NULL)
			return ;
		(*envp)++;
	}
}
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i])
	{
		i++;
	}
	return (str1[i] - str2[i]);
}
char	*find_path_of_cmd_helper(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return ("cd");
	else if (ft_strcmp(command, "pwd") == 0)
		return ("pwd");
	else if (ft_strcmp(command, "export") == 0)
		return ("export");
	else if (ft_strcmp(command, "unset") == 0)
		return ("unset");
	else if (ft_strcmp(command, "env") == 0)
		return ("env");
	else if (ft_strcmp(command, "exit") == 0)
		return ("exit1");
	else
		return (NULL);
}
char	*find_path_of_cmd(char *command, char **envp)
{
	char	**all_path;
	char	*cmd_path;
	char	*temp;
	int		i;

	find_the_word_path_in_envp(&envp);
	all_path = ft_split(*envp + 5, ':');
	i = 0;
	while (all_path[i] != NULL)
	{
		temp = ft_strjoin(all_path[i], "/");
		cmd_path = ft_strjoin(temp, command);
		free(temp);
		if (access(cmd_path, X_OK) == 0)
		{
			free_array(all_path);
			
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_array(all_path);
	return (find_path_of_cmd_helper(command));
}
token_type	check_delimeter1(char *splitted_token)
{
	token_type	type;

	if (ft_strcmp(splitted_token, ">>") == 0)
	{
		type = AOUTPUT_REDIRECTION;
		return (type);
	}
	else if (ft_strcmp(splitted_token, "<<") == 0)
	{
		type = HERE_DOC;
		return (type);
	}
	else if (ft_strcmp(splitted_token, "~") == 0)
	{
		type = TILDE;
		return (type);
	}
	else if (ft_strcmp(splitted_token, "-") == 0)
	{
		type = MINUS;
		return (type);
	}
	else
		return (0);
}
token_type	check_delimeter2(char *splitted_token)
{
	token_type	type;

	if (ft_strcmp(splitted_token, "|") == 0)
	{
		type = PIPE;
		return (type);
	}
	else if (ft_strcmp(splitted_token, ">") == 0)
	{
		type = SOUTPUT_REDIRECTION;
		return (type);
	}
	else if (ft_strcmp(splitted_token, "<") == 0)
	{
		type = SINPUT_REDIRECTION;
		return (type);
	}
	else
		return (0);
}
token_type	check_delimeter3(char *splitted_token, char **envp)
{
	token_type	type;

	if (ft_strcmp(splitted_token, "..") == 0)
	{
		type = TWO_POINTS;
		return (type);
	}
	if (access(splitted_token, F_OK) == 0)
	{
		type = DIRECTORY;
		return (type);
	}
	else if (find_path_of_cmd(splitted_token, envp))
	{
		type = COMMAND;
		return (type);
	}
	else
	{
		type = WORD;
		return (type);
	}
}
token_type	check_delimeter(char *splitted_token, char **envp)
{
	token_type	type;

	if (check_delimeter1(splitted_token) != 0)
	{
		type = check_delimeter1(splitted_token);
		return (type);
	}
	else if (check_delimeter2(splitted_token) != 0)
	{
		type = check_delimeter2(splitted_token);
		return (type);
	}
	else
	{
		type = check_delimeter3(splitted_token, envp);
		return (type);
	}
}

void input_to_linked_list_h(t_token **head,t_token *new)
{
	(*head)->next = new;
	new->prev = (*head);
	(*head) = new;
}
void remove_empty_nodes(t_token **head)
{
    t_token *temp;
    t_token *temp1;
    while ((*head))
    {
        if(check_if_null((*head)->token) == 0)
        {
			if((*head) -> next == NULL){
				 temp = (*head)->prev;
            	temp1=(*head);
				temp -> next = NULL;
				free(temp1);
			}
			else if(((*head) -> next != NULL) && ((*head) -> prev != NULL))
			{
            temp = (*head)->prev;
            temp1=(*head);
            (*head) = (*head)->next;
            temp ->next = (*head);
            (*head)->prev = temp;
			free(temp1);
			}
			else if((*head) -> prev == NULL) 
			{
				temp = (*head) ->next;
				temp1 = (*head);
				temp -> prev = NULL;
				free(temp1);
			}
			
        }
        (*head) = (*head)->next;
    }
}
t_token	*input_to_linked_list(char **input, char **envp)
{
	int		i;
	int		type;
	t_token	*head;
	t_token	*new;
	t_token	*print;

	i = 0;
	head = NULL;
	new = NULL;
	print = NULL;
	while (input[i])
	{
		type = check_delimeter(input[i], envp);
		new = create_node_token(ft_strdup(input[i]), type, built_in_or_not(input[i]));
		if (head == NULL)
		{
			head = new;
			print = head;
		}
		else
			input_to_linked_list_h(&head,new);
		i++;
	}
	return (print);
}
// int check_if_commmand(t_token *head )
// {
// 	if(head -> prev ==NULL)
// 		return (1);
// 	else if (strcmp(head->prev->token,"|") == 0)
// 		return (1);
// 	else 
// 		return (0);
// }

