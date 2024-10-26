/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:49:56 by schaaban          #+#    #+#             */
/*   Updated: 2024/10/26 09:53:08 by wasmar           ###   ########.fr       */
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
		if(*input)
			add_history(input);
		main_helper(input, my_envp);
	}
	return (0);
}

int	check_if_NULL(char *input)
{
	int	i;

	i = 0;
	int non_space_count = 0; 
	if (input == NULL)
		return (0); 
	while (input[i] != '\0')
	{
		if (input[i] != ' ')
			non_space_count++;
		i++;
	}
	return (non_space_count > 0 ? 1 : 0);// fix this
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
	 if (head->next && head->prev && head->next->type == WORD
		&& head->prev->type == PIPE)
	{
		if (head->next->next && head->next->next->type == PIPE)
			return (3);
	}
	 if (head->next && head->next->type == PIPE)
		return (1);
	if (head->next && head->next->type == WORD)
	{
		if (head->next->next && head->next->next->type == PIPE)
			return (1);
	}
	 if (head->prev && head->prev->type == PIPE)
		return (2);
	if(head->next && head->next->next && (head->next->type == DIRECTORY || head->next->type == WORD ) && head->next->next->type == AOUTPUT_REDIRECTION)
	{
		return (4);
	}
	if(head->next && head->next->type ==AOUTPUT_REDIRECTION)
	{
		return (4);
	}
	return (0);
}
#include <fcntl.h>     // For open
void handle_dups(int check_pipe, int *pipefd, int input_fd,t_token *head)
{
	int file_descriptor = 0;
	if(check_pipe == 2)
	{
		dup2(input_fd,0);
		close(input_fd);
		close(pipefd[1]);
	}
	else if(check_pipe == 1)
	{
		dup2(pipefd[1],1);
		close(input_fd);
		close(pipefd[1]);
	}
	else if(check_pipe == 3)
	{
		dup2(input_fd,0);
		dup2(pipefd[1],1);
		close(input_fd);
		close(pipefd[1]);
	}
	else if(check_pipe == 4)
	{
		if(head->next && head->next->type == DIRECTORY)
		{
		 file_descriptor = open(head->next->next->next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if(head->next && head->next->type == AOUTPUT_REDIRECTION)
		{
		file_descriptor = open(head->next->next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		dup2(file_descriptor,1);
		close(file_descriptor);		
	}
}
int pipe_count(t_token *head)
{
	int pipes;
	pipes = 0;
	while(head != NULL)
	{
		if(head -> type == PIPE)
		{
			pipes ++;
		}
		head = head -> next;
	}
	return(pipes);
}
char **array_complicated_execute(t_token *head)
{
	char **current_command;
	int len;

	len = 0;
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
			}
			else
			{
				current_command = malloc(2 * sizeof(char *));
				len = ft_strlenn(head->token) + 1;
				current_command[0] = malloc(len * sizeof(char));
				strcpy(current_command[0], head->token);
				current_command[1] = NULL;
			}
			return(current_command);
}
void	complicated_execute(t_env *my_envp, t_token *head, char *envp[])
{
	int		pipefd[2];
	int input_fd;

	input_fd = STDIN_FILENO;
	while (head != NULL)
	{
		if((head -> next && head -> next -> type == PIPE))
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe failed");
				exit(EXIT_FAILURE);
			}
		}
		if (head->type == COMMAND)
			run_command(head, array_complicated_execute(head), envp, my_envp, pipefd,input_fd);
		close(pipefd[1]);
		input_fd = pipefd[0];
		head = head->next;
	}
}
void run_built_ins(t_token *head,char **envp, t_env *my_envp,int *pipefd,int input_fd,char **current_command)
{
	(void)envp;
	(void)current_command;
	if (strcmp(head->token, "env") == 0)
	{
		handle_dups(check_pipe(head),pipefd,input_fd,head);
		 print_listt(my_envp);
		exit(EXIT_SUCCESS);
	}
}
void external_commands(t_token *head,char **envp, t_env *my_envp,int *pipefd,int input_fd,char **current_command)
{
		(void)my_envp;
			 char	*path;
	         handle_dups(check_pipe(head),pipefd,input_fd,head);

			path = find_path_of_cmd(head->token, envp);
			if (execve(path, current_command, envp) == -1)
				printf("execve failed");
			exit(EXIT_SUCCESS);
}
void run_command_helper(t_token *head,char **envp, t_env *my_envp,int *pipefd,int input_fd,char **current_command)
{
		if ((strcmp(head->token, "env") == 0) || (strcmp(head -> token, "echo") == 0) || (strcmp(head -> token, "unset") == 0) || (strcmp(head -> token, "export") == 0))
		{
			run_built_ins(head,envp,my_envp,pipefd,input_fd,current_command);
		}
		// else if((strcmp(head -> token, "cd") == 0) || (strcmp(head -> token, "pwd") == 0) || (strcmp(head -> token, "exit") == 0))
		// {

		// }
		else
		{
			external_commands(head,envp,my_envp,pipefd,input_fd,current_command);
		}
}

void	run_command(t_token *head, char **current_command, char **envp,
		t_env *my_envp, int *pipefd,int input_fd)
{
	int		forkid;
	forkid = fork();
	if (forkid == 0)
	{
		run_command_helper(head,envp,my_envp,pipefd,input_fd,current_command);
	}
	else if (forkid > 0)
	{
		close(pipefd[1]);
		waitpid(forkid, NULL, 0);
	}
	else
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
}


