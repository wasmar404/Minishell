/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:49:56 by schaaban          #+#    #+#             */
/*   Updated: 2024/10/24 13:35:26 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#define RESET "\033[0m"
#define BOLD_CYAN "\033[1;36m"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_env	*head;
	char	**my_envp;
	char	*prompt;

	(void)ac;
	(void)av;
	(void)input;
	head = env_to_linked_list(envp);
	(void)head;
	my_envp = env_to_array(head);
	(void)my_envp;
	prompt = BOLD_CYAN "sw_shell> " RESET;
	while (1)
	{
		input = readline(prompt);
		main_helper(input, my_envp);
	}
	return (0);
}

int	check_if_NULL(char *input)
{
	int	i;

	i = 0;
	int non_space_count = 0; // Renamed j to non_space_count for clarity
	// Check if input is NULL
	if (input == NULL)
		return (0); // Return 0 if input is NULL
	while (input[i] != '\0')
	{
		if (input[i] != ' ')
			non_space_count++;
		i++;
	}
	// Return 0 if no non-space characters were found
	return (non_space_count > 0 ? 1 : 0);
}

void	main_helper(char *input, char **envp)
{
	char	**splitted_input;
	t_token	*head;
	t_env	*head_env;

	if (check_if_NULL(input) == 0)
	{
		return ;
	}
	splitted_input = token_split(input);
	// (void)splitted_input;
	// (void)envp;
	head = input_to_linked_list(splitted_input, envp);
	head_env = env_to_linked_list(envp);
	complicated_execute(head_env, head, envp);
}
void	print_list(t_token *head)
{
	while (head != NULL)
	{
		printf("%s\n", head->token);
		head = head->next;
	}
}
int	check_pipe(t_token *head)
{
	if (head->next && head->prev && head->next->type == PIPE
		&& head->prev->type == PIPE)
		return (3);
	else if (head->next && head->prev && head->next->type == WORD
		&& head->prev->type == PIPE)
	{
		if (head->next->next && head->next->next->type == PIPE)
			return (3);
	}
	else if (head->next && head->next->type == PIPE)
		return (1);
	else if (head->next && head->next->type == WORD)
	{
		if (head->next->next && head->next->next->type == PIPE)
			return (1);
	}
	else if (head->prev && head->prev->type == PIPE)
		return (2);
	else
		return (0);
	return (0);
}
void	run_command(t_token *head, char **current_command, char **envp,
			t_env *my_envp, int *pipefd);
void	complicated_execute(t_env *my_envp, t_token *head, char *envp[])
{
	char	**current_command;
	int		len;
	int		pipefd[2];

	len = 0;
	// char buffer[3];
	(void)my_envp;
	(void)envp;
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	while (head != NULL)
	{
		if (head->type == COMMAND)
		{
			if (head->next && (head->next->type == WORD
					|| head->next->type == DIRECTORY))
			{
				current_command = malloc(3 * sizeof(char *));
				len = ft_strlenn(head->token) + 1;
				current_command[0] = malloc(len * sizeof(char));
				strcpy(current_command[0], head->token);
				len = ft_strlenn(head->next->token) + 1;
				current_command[1] = malloc(len * sizeof(char));
				strcpy(current_command[1], head->next->token);
				current_command[2] = NULL;
				// print_array(current_command);
			}
			else
			{
				current_command = malloc(2 * sizeof(char *));
				len = ft_strlenn(head->token) + 1;
				current_command[0] = malloc(len * sizeof(char));
				strcpy(current_command[0], head->token);
				current_command[1] = NULL;
				// print_array(current_command);
			}
			run_command(head, current_command, envp, my_envp, pipefd);
			// read(pipefd[0], buffer, 3);
			// printf("Child received: %s\n", buffer);
			// close(pipefd[1]);
			// close(pipefd[0]);
			// }
		}
		if (head != NULL)
		{
			close(pipefd[1]); // Close the write end in the parent
		}
		head = head->next;
	}
}

void	run_command(t_token *head, char **current_command, char **envp,
		t_env *my_envp, int *pipefd)
{
	int		forkid;
	char	*path;

	forkid = fork();
	(void)my_envp;
	if (forkid == 0)
	{
		if (strcmp(head->token, "env") == 0)
		{
			dup2(pipefd[1], 1);
			close(pipefd[0]);
			close(pipefd[1]);
			print_listt(my_envp);
			exit(EXIT_SUCCESS);
		}
		else
		{
			dup2(pipefd[0], 0);
			close(pipefd[0]);
			close(pipefd[1]);
			path = find_path_of_cmd(head->token, envp);
			if (execve(path, current_command, envp) == -1)
				printf("execve failed");
			exit(EXIT_SUCCESS);
		}
	}
	else if (forkid > 0)
	{
		// close(pipefd[1]);
		waitpid(forkid, NULL, 0);
	}
	else
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
}
