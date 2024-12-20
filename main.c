/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:49:56 by schaaban          #+#    #+#             */
/*   Updated: 2024/12/20 13:55:24 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_env	*head;
	char	**my_envp;

	(void)ac;
	(void)av;
	head = env_to_linked_list(envp);
	my_envp = env_to_array(head);
	while (1)
	{
		input = readline(BOLD_CYAN "sw_shell> " RESET);
		if(*input)
			add_history(input);
		main_helper(input, my_envp,&head);
	}
	return (0);
}

int check_if_null(char *input)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	if(input == NULL)
		return (0);
	while(input[i])
	{
		if(input[i] != ' ')
			j++;
		i++;
	}
	if(j == 0)
		return(0);
	else
		return(1);
	
}
void	main_helper(char *input, char **envp,t_env **env_linked)
{
	char	**splitted_input;
	t_token	*head;

	if (check_if_null(input) == 0)
		return ;
	splitted_input = token_split(input);
	head = input_to_linked_list(splitted_input, envp);
	complicated_execute(env_linked, head, envp);
}
void super_complicated_handle_dups(t_token *head,int *pipefd, int input_fd)
{
	t_token *current = head;
	t_token *current_input =NULL;
	t_token *current_output =NULL;
		if (input_fd != STDIN_FILENO) 
		{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
		}
	check_back_and_front(current,&current_input,&current_output,current->next);
	dups1(current_input,current_output,pipefd);
	dups2(current,current_output,input_fd);
	close(pipefd[0]);
	close(pipefd[1]);
}
void dups2(t_token *current_input,t_token *current_output,int input_fd)
{
	int fd;
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
void dups1(t_token *current_input,t_token *current_output,int *pipefd)
{
	int fd;
	if(current_input && current_input->type == HERE_DOC)
	{
		fd = open("temp", O_WRONLY | O_CREAT | O_APPEND , 0644);
		heredoc(current_input->next->token,fd);
		close(fd);
		fd = open("temp",O_RDONLY);
		dup2(fd,0);
		close(fd);
		unlink("temp");
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
}
void check_back_and_front(t_token *head_back,t_token **current_input,t_token **current_output,t_token *current)
{
	int flag;
	
	flag = 0;
	while(head_back)
	{
		if(head_back ->type == SINPUT_REDIRECTION || head_back ->type == PIPE || head_back ->type ==HERE_DOC)
		{
			(*current_input) = head_back;
			break;
		}
		if(head_back->type == AOUTPUT_REDIRECTION || head_back ->type == SOUTPUT_REDIRECTION)
		{
			(*current_output) = head_back;
			flag++;
		}
		head_back = head_back -> prev;
	}
	while(current != NULL && current->type != COMMAND )
	{
		if((current->type == AOUTPUT_REDIRECTION || current->type == SOUTPUT_REDIRECTION || current->type == PIPE )&& flag == 0)
			(*current_output)=current;
		if((current->type == SINPUT_REDIRECTION || current->type == HERE_DOC))
			(*current_input) = current;
		current = current->next;
	}
}

int pipe_count(t_token *head)
{
	int pipes;
	pipes = 0;
	while(head != NULL)
	{
		if(head -> type == PIPE || head->type == AOUTPUT_REDIRECTION)
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
		if(temp->type == SINPUT_REDIRECTION || temp->type == SOUTPUT_REDIRECTION || temp->type == AOUTPUT_REDIRECTION || temp->type == HERE_DOC)
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
		if(temp->type == SINPUT_REDIRECTION || temp->type == SOUTPUT_REDIRECTION || temp->type == AOUTPUT_REDIRECTION || temp->type == HERE_DOC)
		{
			break;  while (wait(NULL) > 0);
		}
		current_command[i]=strdup(temp->token);
		 i++;
		 temp = temp ->  next;
	}
	current_command[i]= NULL;
	return(current_command);

}
void	complicated_execute(t_env **my_envp, t_token *head, char *envp1[])
{
	int		pipefd[2];
	int input_fd;
	(void)envp1;
	input_fd = STDIN_FILENO;
	t_token *temp;
	pid_t pid ;
	t_token *head1 = head;

	while (head != NULL)
	{
			char **envp = env_to_array(*my_envp);

		 if (head->type == COMMAND)
		 {
			temp = head->next;
			while(temp && temp->type != SOUTPUT_REDIRECTION && temp->type != COMMAND)
			{
				if(temp->type == PIPE)
				{
					if (pipe(pipefd) == -1)
					{
						perror("pipe failed");
						exit(EXIT_FAILURE);
					}
					break;
				}
				else{
					pipefd[0]=-1;
					pipefd[1]=-1;
				}
				temp = temp -> next;
			}
			if(pipe_count(head1) == 0 && ((strcmp(head->token, "env") == 0) || (strcmp(head -> token, "echo") == 0) || 
					(strcmp(head -> token, "cd") == 0) || (strcmp(head -> token, "pwd") == 0) || (strcmp(head -> token,"export") == 0) || (strcmp(head -> token,"unset") == 0) || (strcmp(head -> token,"exit") == 0)) )
			{
				// run_command_helper(head,envp,my_envp,pipefd,input_fd,array_complicated_execute(head));
				run_built_ins1(head,envp,my_envp,pipefd,input_fd,array_complicated_execute(head));
			}
			else{
			pid = fork();
			
            if (pid == 0)
            {
				run_command_helper(head,envp,my_envp,pipefd,input_fd,array_complicated_execute(head));
                exit(EXIT_SUCCESS);
            }
            else if (pid > 0)
            {
                if (input_fd != STDIN_FILENO)
                    close(input_fd);
                 input_fd = pipefd[0];
            }
            else
            {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
        }
		close(pipefd[1]);}
		head = head->next;
	}
			    while (wait(NULL) > 0);
}
int find_var_name_return(t_env *my_envp,char *var_name)
{
    while(my_envp != NULL)
    {
        if(ft_strcmp(my_envp -> type,var_name) == 0)
        {
			return(1);
        }
        my_envp = my_envp -> next;
    }
	return(0);
}
void run_built_ins1(t_token *head,char **envp, t_env **my_envp,int *pipefd,int input_fd,char **current_command)
{
	(void)envp;
	(void)current_command;
	(void)pipefd;
	(void)input_fd;
	if ((strcmp(head->token, "env") == 0) && (find_var_name_return((*my_envp),"PATH") == 1))
		print_listt((*my_envp));
	if(strcmp(head->token,"echo") == 0)
		echo_main(head,(*my_envp));
	if(strcmp(head->token,"pwd") == 0)
		main_pwd();
	if(strcmp(head->token,"cd") == 0)
		main_cd(head,my_envp);
	if(strcmp(head->token,"export") == 0)
		export_main(my_envp,head);
	if(strcmp(head->token,"unset") == 0)
	{
		if (head->next == NULL || head->next->token == NULL || head->next->token[0] == '\0')
        	return;
		if(invalid_option(head) == 0)
			return ;
		 main_unset1(my_envp,head -> next -> token);
	}
	if(strcmp(head -> token, "exit") == 0)
		exit(EXIT_SUCCESS);
}
void run_built_ins(t_token *head,char **envp, t_env **my_envp,int *pipefd,int input_fd,char **current_command)
{
	(void)envp;
	(void)current_command;

	if ((strcmp(head->token, "env") == 0) && (find_var_name_return((*my_envp),"PATH") == 1))
	{
				super_complicated_handle_dups(head,pipefd,input_fd);
		 print_listt((*my_envp));
		exit(EXIT_SUCCESS);
	}
	if(strcmp(head->token,"echo") == 0)
	{
		super_complicated_handle_dups(head,pipefd,input_fd);
		echo_main(head,(*my_envp));
		exit(EXIT_SUCCESS);
	}
			if(strcmp(head->token,"pwd") == 0)
	{
		super_complicated_handle_dups(head,pipefd,input_fd);
		main_pwd();
		exit(EXIT_SUCCESS);
	}
	if(strcmp(head->token,"cd") == 0)
	{
		super_complicated_handle_dups(head,pipefd,input_fd);
		main_cd(head,my_envp);
		exit(EXIT_SUCCESS);
	}
	if(strcmp(head->token,"export") == 0)
	{
		printf("fetet lahon?");
		fflush(stdout);
		super_complicated_handle_dups(head,pipefd,input_fd);
		export_main(my_envp,head);
		exit(EXIT_SUCCESS);
	}
	if(strcmp(head->token,"unset") == 0)
	{
		if (head->next == NULL || head->next->token == NULL || head->next->token[0] == '\0')
        	return;
		// if(invalid_option(head) == 0)
        // 	return ;
		super_complicated_handle_dups(head,pipefd,input_fd);
		main_unset1(my_envp,head -> next -> token);
		exit(EXIT_SUCCESS);
	}
	if(strcmp(head -> token, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	
}
void external_commands(t_token *head,char **envp, t_env *my_envp,int *pipefd,int input_fd,char **current_command)
{
		(void)my_envp;
			 char	*path;
			super_complicated_handle_dups(head,pipefd,input_fd);
			path = find_path_of_cmd(head->token, envp);
			if (execve(path, current_command, envp) == -1)
				printf("execve failed");
			exit(EXIT_SUCCESS);
}
void run_command_helper(t_token *head,char **envp, t_env **my_envp,int *pipefd,int input_fd,char **current_command)
{
		if ((strcmp(head->token, "env") == 0) || (strcmp(head -> token, "echo") == 0) || (strcmp(head -> token, "cd") == 0) || (strcmp(head -> token, "pwd") == 0))
		{
			run_built_ins(head,envp,my_envp,pipefd,input_fd,current_command);
		}
		else if((strcmp(head -> token, "export") == 0) || (strcmp(head -> token, "unset") == 0) || (strcmp(head -> token, "exit") == 0))
		{
			run_built_ins(head,envp,my_envp,pipefd,input_fd,current_command);		
		}
		else
		{
			external_commands(head,envp,(*my_envp),pipefd,input_fd,current_command);
		}
}

void heredoc(char *str,int fd)
{
	char *input;
	while(1)
	{
		input = readline("heredoc ");
		if(strcmp(str,input) == 0)
		{
			break;
		}
		write(fd,input,ft_strlenn(input));
		 write(fd,"\n",1);
	}
}