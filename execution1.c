/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:03:54 by wasmar            #+#    #+#             */
/*   Updated: 2025/03/22 22:48:14 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
void check_and_create_pipe(t_token *temp,int *pipefd,int *flag);

void	complicated_execute(t_env **my_envp, t_token *head,t_shell *shell)
{
int		pipefd[2];
int		status;
char	**envp;
int		input_fd;
t_token	*temp;
t_token	*current;
int		saved_stdin;
int		saved_stdout;
int		flag;
int		flag20;
int		fd;

input_fd = STDIN_FILENO;
shell->pid = -1;
current = head;
saved_stdin = dup(STDIN_FILENO);
saved_stdout = dup(STDOUT_FILENO);
flag = 0;
flag20 = 0;
if (strcmp(current->token, "exit") == 0)
{
    exit_command(current, shell);
}
while (current != NULL)
{
    envp = env_to_array(*my_envp,shell);
    if (command_exists(head) == 0)
    {
        if (current->type == HERE_DOC)
            heredoc_dup(current);
        else if (current->type == SOUTPUT_REDIRECTION)
            s_out_redirection(current);
        else if (current->type == AOUTPUT_REDIRECTION)
            a_out_redirection(current);
    }
    if (current->type == COMMAND)
    {
        flag = 0;
        temp = current->next;
        check_and_create_pipe(temp,pipefd,&flag);

        if (pipe_count(head) == 0 && current->built_in_or_not == true)
        {
            flag20 = 1;
            run_built_ins(current, my_envp, pipefd, input_fd, 0, flag,
                shell);
            dup2(saved_stdin, STDIN_FILENO);
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdin);
            close(saved_stdout);
        }
        else
        {
            shell->pid = fork();
            if (shell->pid == 0)
            {
                restore_signals();
                if (shell->exit_code == 127)
                {
                    fd = open("/dev/null", O_RDONLY);
                    dup2(fd, STDIN_FILENO);
                }
    
                add_shell_level(my_envp, current, &envp,shell);
                run_command_helper(current, envp, my_envp, pipefd, input_fd,
                array_complicated_execute(current,shell), flag, shell);
            }
            else if (shell->pid > 0)
            {
                if (input_fd != STDIN_FILENO && pipefd[0] != -1)
                    close(input_fd);
                input_fd = pipefd[0];
            }
            else
            {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
        }
        if (flag == 1)
            close(pipefd[1]);
    }
    current = current->next;
}

if (flag20 == 0)
{
    ignore_signals();
    while (wait(&status) > 0)
        ;
    main_signal();
    if (WIFEXITED(status)) 
    {
        shell->exit_code = WEXITSTATUS(status); 
    }
    else if (WIFSIGNALED(status))
    {
        shell->exit_code = 128 + WTERMSIG(status);
    }
}
}

/**
 * check_and_create_pipe - Checks if there is a pipe after a command until another command is reached.
 * If found, the pipe is created.
 * 
 * @head: A double pointer to the next node after the command.
 * @pipe_fd: An array of two integers representing the file descriptors for the pipe.
 * @flag: A pointer to a flag that is incremented when a pipe is created.
 * 
 * Description:
 * This function iterates through the linked list of tokens, starting from the node after the command. 
 * If it encounters a `PIPE` token before a `COMMAND` token, it creates a pipe.  
 * If pipe creation fails, the function prints an error message and exits.  
 * If no pipe is found, `pipe_fd` is set to `-1, -1`.
 */

void check_and_create_pipe (t_token *head,int *pipe_fd,int *flag)
{
    while (head && (head)->type != COMMAND)
    {
        if (head->type == PIPE)
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("pipe failed");
                // add the free function
                exit(EXIT_FAILURE);
            }
            (*flag)++;
            break ;
        }
        else
        {
            pipe_fd[0] = -1;
            pipe_fd[1] = -1;
        }
        head = head->next;
    }
}