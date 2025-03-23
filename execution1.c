/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:03:54 by wasmar            #+#    #+#             */
/*   Updated: 2025/03/23 15:10:01 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
void check_and_create_pipe(t_token *temp,int *pipefd,int *flag);
typedef struct t_exe
{
    int		saved_stdin;
    int		saved_stdout;
    int     pipefd[2];
    int status;
    int   input_fd;
    int fd;
    char	**envp;
    int		fork_flag;
    int pipe_flag;
}t_exe;
void	complicated_execute(t_env **my_envp, t_token *head,t_shell *shell)
{
t_exe exe;
t_token	*temp;
t_token	*current;
// int		flag;

exe.input_fd = STDIN_FILENO;
shell->pid = -1;
current = head;
exe.saved_stdin = dup(STDIN_FILENO);
exe.saved_stdout = dup(STDOUT_FILENO);
exe.pipe_flag = 0;
exe.fork_flag= 0;
if (strcmp(current->token, "exit") == 0)
{
    exit_command(current, shell);
}
while (current != NULL)
{
    exe.envp = env_to_array(*my_envp,shell);
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
        exe.pipe_flag = 0;
        temp = current->next;
        check_and_create_pipe(temp,exe.pipefd,&(exe.pipe_flag));

        if (pipe_count(head) == 0 && current->built_in_or_not == true)
        {
            exe.fork_flag = 1;
            run_built_ins(current, my_envp, exe.pipefd, exe.input_fd, 0, exe.pipe_flag,
                shell);
            dup2(exe.saved_stdin, STDIN_FILENO);
            dup2(exe.saved_stdout, STDOUT_FILENO);
            close(exe.saved_stdin);
            close(exe.saved_stdout);
        }
        else
        {
            shell->pid = fork();
            if (shell->pid == 0)
            {
                restore_signals();
                if (shell->exit_code == 127)
                {
                    exe.fd = open("/dev/null", O_RDONLY);
                    dup2(exe.fd, STDIN_FILENO);
                }
    
                add_shell_level(my_envp, current, &(exe.envp),shell);
                run_command_helper(current, (exe.envp), my_envp, exe.pipefd, exe.input_fd,
                array_complicated_execute(current,shell), exe.pipe_flag, shell);
            }
            else if (shell->pid > 0)
            {
                if (exe.input_fd != STDIN_FILENO && exe.pipefd[0] != -1)
                    close(exe.input_fd);
                exe.input_fd = exe.pipefd[0];
            }
            else
            {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
        }
        if (exe.pipe_flag == 1)
            close(exe.pipefd[1]);
    }
    current = current->next;
}

if (exe.fork_flag == 0)
{
    ignore_signals();
    while (wait(&(exe.status)) > 0)
        ;
    main_signal();
    if (WIFEXITED(exe.status)) 
    {
        shell->exit_code = WEXITSTATUS(exe.status); 
    }
    else if (WIFSIGNALED(exe.status))
    {
        shell->exit_code = 128 + WTERMSIG(exe.status);
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