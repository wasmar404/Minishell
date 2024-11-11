/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:49:56 by schaaban          #+#    #+#             */
/*   Updated: 2024/11/11 09:02:19 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

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
		printf("%s %d\n", head->token,head->type);
		head = head->next;
	}
}

void super_complicated_handle_dups(t_token *head,int *pipefd, int input_fd)
{
	int input_flag = 0;
	int output_flag = 0;
	int input_pipe_flag = 0;
	int output_pipe_flag = 0;
	t_token *current = head;
	t_token *currentback = head;
	t_token *current_input =NULL;
	t_token *current_output =NULL;
	int fd;
		
    while (currentback)
    {
        if (currentback->type == SINPUT_REDIRECTION || currentback->type == PIPE)
        {

			if(currentback->type == PIPE)
			{
				input_pipe_flag++;
			}
            input_flag++;
            current_input = currentback;
            break;
        }
        currentback = currentback->prev;
    }
	current = current ->next;
	while(current != NULL && current->type != COMMAND)
	{

		if(current->type == AOUTPUT_REDIRECTION || current->type == SOUTPUT_REDIRECTION)
		{
			output_flag++;;
			current_output=current;
		}
		if((current->type == SINPUT_REDIRECTION || current->type == HERE_DOC) && input_flag == 0)
		{
			input_flag++;
			current_input = current;
		}
		if(current->type == PIPE)
		{
			output_pipe_flag++;
			output_flag++;
			current_output=current;
		}
		current = current->next;
	}
	if (current_input && current_input->type == SINPUT_REDIRECTION)
    {
        fd = open(current_input->next->token, O_RDONLY, 0644);
        dup2(fd, 0);
        close(fd);
    }
    if (current_output && current_output->type == PIPE)
    {
		dup2(pipefd[1],1);
		close(pipefd[1]);
    }
	if(current_input && current_input->type == PIPE)
	{
		dup2(input_fd,0);
		close(input_fd);
	}
	if(current_output && current_output->type == AOUTPUT_REDIRECTION)
	{
		fd = open(current_output->next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd,1);
		close(fd);
	}
	if(current_output && current_output->type == SOUTPUT_REDIRECTION)
	{
		fd = open(current_output->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd,1);
		close(fd);
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
	int i = 0;
	t_token *temp = head;
	while(temp != NULL &&  temp->type != PIPE)
	{
		len++;
		if(temp->type == COMMAND && temp != head)
		{
			break;
		}
		if(temp->type == SINPUT_REDIRECTION || temp->type == SOUTPUT_REDIRECTION || temp->type == AOUTPUT_REDIRECTION)
		{
			break;
		}
		temp = temp ->next;
	}
	current_command = malloc((len+1) *sizeof(char *));
	temp = head;
	while(temp != NULL && temp->type != PIPE)
	{
		if(temp->type == COMMAND && temp != head)
		{
			break;
		}
		if(temp->type == SINPUT_REDIRECTION || temp->type == SOUTPUT_REDIRECTION || temp->type == AOUTPUT_REDIRECTION)
		{
			break;
		}
		current_command[i]=strdup(temp->token);
		 i++;
		 temp = temp ->  next;
	}
	current_command[i]= NULL;
	return(current_command);

}
void	complicated_execute(t_env *my_envp, t_token *head, char *envp[])
{
	int		pipefd[2];
	int input_fd;

	input_fd = STDIN_FILENO;
	t_token *temp;
	(void)input_fd;
	(void)my_envp;
	(void)envp;
	while (head != NULL)
	{
		 if (head->type == COMMAND)
		 {
			temp = head->next;
			while(temp && temp->type != SOUTPUT_REDIRECTION && temp->type != COMMAND)
			{
				if(temp->type == PIPE)
				{
					fflush(stdout);
					if (pipe(pipefd) == -1)
					{
						perror("pipe failed");
						exit(EXIT_FAILURE);
					}
					break;
				}
				temp = temp -> next;
			}
			run_command(head, array_complicated_execute(head), envp, my_envp, pipefd,input_fd);
		 }
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
				super_complicated_handle_dups(head,pipefd,input_fd);
		 print_listt(my_envp);
		exit(EXIT_SUCCESS);
	}
	if(strcmp(head->token,"echo") == 0)
	{
		super_complicated_handle_dups(head,pipefd,input_fd);
		echo_main(head,my_envp);
		exit(EXIT_SUCCESS);
	}
}
void external_commands(t_token *head,char **envp, t_env *my_envp,int *pipefd,int input_fd,char **current_command)
{
		(void)my_envp;
			 char	*path;
			super_complicated_handle_dups(head,pipefd,input_fd);
			printf("hello is madame grep working?");
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