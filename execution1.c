/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:03:54 by wasmar            #+#    #+#             */
/*   Updated: 2025/03/22 20:46:18 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
void pipe_check(t_token **temp,int *pipefd,int *flag);
void	complicated_execute(t_env **my_envp, t_token *head, char *envp1[],
    t_shell *exitcode,t_shell *shell)
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

// pipefd = malloc(2 * sizeof(int));
(void)envp1;
input_fd = STDIN_FILENO;
// pid_t pid = -1;
exitcode->pid = -1;
current = head;
saved_stdin = dup(STDIN_FILENO);
saved_stdout = dup(STDOUT_FILENO);
flag = 0;
flag20 = 0;
if (strcmp(current->token, "exit") == 0)
{
    exit_command(current, exitcode);
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
        pipe_check(&temp,pipefd,&flag);
        // while (temp && temp->type != COMMAND)
        // {
        //     if (temp->type == PIPE)
        //     {
        //         if (pipe(pipefd) == -1)
        //         {
        //             perror("pipe failed");
        //             exit(EXIT_FAILURE);
        //         }
        //         flag++;
        //         break ;
        //     }
        //     else
        //     {
        //         pipefd[0] = -1;
        //         pipefd[1] = -1;
        //     }
        //     temp = temp->next;
        // }
        if (pipe_count(head) == 0 && current->built_in_or_not == true)
        {
            flag20 = 1;
            run_built_ins(current, my_envp, pipefd, input_fd, 0, flag,
                exitcode);
            dup2(saved_stdin, STDIN_FILENO);
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdin);
            close(saved_stdout);
        }
        else
        {
            exitcode->pid = fork();
            if (exitcode->pid == 0)
            {
                restore_signals();
                if (exitcode->exit_code == 127)
                {
                    fd = open("/dev/null", O_RDONLY);
                    dup2(fd, STDIN_FILENO);
                }
                // flag20 = 1;
                // if (check_command(current->token, envp) == 0)
                // {
                //     // ft_putendl_fd_two(current->token,
                    // ": command not found", 2);
                //     exit(127);
                // }
                add_shell_level(my_envp, current, &envp,shell);
                run_command_helper(current, envp, my_envp, pipefd, input_fd,
                    array_complicated_execute(current,shell), flag, exitcode);
                // exit(exit_code);
            }
            else if (exitcode->pid > 0)
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
// if(flag20 == 0)
// {
//     while (wait(&status) > 0);
//      exit_code  = status;
// }
if (flag20 == 0)
{
    ignore_signals();
    while (wait(&status) > 0)
        ;
    main_signal();
    if (WIFEXITED(status)) // Check if the child exited normally
    {
        exitcode->exit_code = WEXITSTATUS(status); // Extract the exit code
        pipefd = malloc(2 * sizeof(int));
    }
    else if (WIFSIGNALED(status))
        // Check if the child was terminated by a signal
    {
        exitcode->exit_code = 128 + WTERMSIG(status);
            // Set exit code to 128 + signal number
    }
}
}
void pipe_check(t_token **temp,int *pipefd,int *flag)
{
    while (*temp && (*temp)->type != COMMAND)
    {
        if ((*temp)->type == PIPE)
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe failed");
                exit(EXIT_FAILURE);
            }
            (*flag)++;
            break ;
        }
        else
        {
            (pipefd)[0] = -1;
            (pipefd)[1] = -1;
        }
        *temp = (*temp)->next;
    }
}