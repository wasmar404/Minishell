/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:22:17 by schaaban          #+#    #+#             */
/*   Updated: 2025/02/06 17:33:16 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
// void here_doc(t_token *head)
// {
//     char *line = NULL;
//     while(1)
//     {
//         line = get_next_line(STDIN_FILENO);
//         if (strncmp(line, head->next->token, strlen(head->next->token)) == 0 
//             && line[strlen(head->next->token)] == '\n') // check why you used strncmp, go back to your chat with gpt
//         {
//             free(line);
//             break;
//         }
//         free(line);
//     }
//     printf("%s",head -> next -> token);
// }
void here_doc(t_token *head, int *fdin)
{
    char temp_filename[] = "/tmp/heredoc_XXXXXX";
    int temp_fd = mkstemp(temp_filename);
    
    if (temp_fd == -1)
    {
        perror("Failed to create temporary file for heredoc");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    while ((line = get_next_line(STDIN_FILENO)) != NULL)
    {
        line[strcspn(line, "\n")] = 0; // Remove newline

        if (strcmp(line, head->next->token) == 0)
        {
            free(line);
            break;
        }

        write(temp_fd, line, strlen(line));
        write(temp_fd, "\n", 1);
        free(line);
    }

    close(temp_fd);
    
    // Reopen the temp file for reading
    *fdin = open(temp_filename, O_RDONLY);
    unlink(temp_filename); // File will be deleted when closed
}

void handle_redirections(t_token *head, int *fdin, int *fdout)
{
    t_token *temp = head;
    *fdin = STDIN_FILENO;
    *fdout = STDOUT_FILENO;
    int fd;

    // im assuming we have to stop the loop when i find a command since a command line that contains multiple redirections takes 1 cmd, so fdin and fdout change..
    // ..when there is another command or something, so create the files and change fdin and out and handle this part of a command line untill there is another cmd.
    //(again im assuming it works like this)
    while(temp && temp -> type != COMMAND) 
    {
        if(temp -> type == HERE_DOC)
            here_doc(temp,fdin);
        if(temp -> type == SINPUT_REDIRECTION)
            *fdin = open(temp->next->token, O_RDONLY, 0644);
        if(temp -> type == SOUTPUT_REDIRECTION)
        {
            if (temp->next->type == DIRECTORY && access(temp->next->token, W_OK) == -1)
            {
                int dev_null = open("/dev/null", O_WRONLY);
                dup2(dev_null, STDOUT_FILENO);
                return;
            }  
            *fdout = open(temp->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        if(temp -> type == AOUTPUT_REDIRECTION)
        {
            if (temp->next->type == DIRECTORY && access(temp->next->token, W_OK) == -1)
            {
                int dev_null = open("/dev/null", O_WRONLY);
                dup2(dev_null, STDOUT_FILENO);
                return;
            }
            *fdout = open(temp->next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        temp = temp -> next;
    }
}
void check_pipes(t_token *head,int *fdin, int *fdout)
{
    t_token *temp = head;
    int pipefd[2];
    while(temp && temp -> type != COMMAND)
    {
        if(temp -> type == PIPE)
        {
            if(pipe(pipefd) == -1)
            {
                perror("pipe failed");
                exit_code = 1;
                exit(EXIT_FAILURE);
            }
            *fdout = pipefd[1];
            *fdin = pipefd[0]; 
            break;
        }
        else
        {
            pipefd[0]=-1;
            pipefd[1]=-1;
        }
        temp = temp -> next;
    }
    
}
void run_built_ins_new(t_token *head, t_env **my_envp)
{
    t_env *env_copy = (*my_envp);//so the var  my_envp does not become null 
    // super_complicated_handle_dups(head,pipefd,input_fd,flag2);
    if ((strcmp(head->token, "env") == 0) && (find_var_name_return((*my_envp),"PATH") == 1))
        exit_code = print_listt((*my_envp));
    if(strcmp(head->token,"echo") == 0)
        exit_code = echo_main(head);
    if(strcmp(head->token,"pwd") == 0)
        exit_code = main_pwd();
    if(strcmp(head->token,"cd") == 0)
        main_cd(head,&env_copy);
    if(strcmp(head->token,"export") == 0)
        export_main(my_envp,head); 
    if(strcmp(head->token,"unset") == 0)
    {
        if (head->next == NULL || head->next->token == NULL || head->next->token[0] == '\0')
        {
            exit_code = 1;
            return;

        }
        if(invalid_option(head) == 0)
        {
            exit_code = 1;
            return ;
        }
        main_unset1(my_envp,head -> next -> token);
    }
    // if(flag == 1)
    //     exit(EXIT_SUCCESS);
}
void execution(t_env **my_envp, t_token *head, char *envp1[])
{
    int pipefd[2];
    pid_t pid;
    int saved_stdin=dup(STDIN_FILENO);
    int saved_stdout=dup(STDOUT_FILENO);
    int fdin = STDIN_FILENO;
    int fdout = STDOUT_FILENO;
    char **envp;

    while(head)
    {
        envp = env_to_array(*my_envp);
        handle_redirections(head,&fdin,&fdout);
        check_pipes(head -> next,&fdin,&fdout);
        dup2(fdin, STDIN_FILENO);
        close(fdin);
        dup2(fdout, STDOUT_FILENO);
        close(fdout);
        if(pipe_count(head) == 0 && ((strcmp(head->token, "env") == 0) || (strcmp(head -> token, "echo") == 0) ||
                (strcmp(head -> token, "cd") == 0) || (strcmp(head -> token, "pwd") == 0) || (strcmp(head -> token,"export") == 0) || (strcmp(head -> token,"unset") == 0) || (strcmp(head -> token,"exit") == 0)) )
        {
            // flag20 = 1;
            run_built_ins_new(head,my_envp);
            dup2(saved_stdin,STDIN_FILENO);
            dup2(saved_stdout,STDOUT_FILENO);
            close(saved_stdin);
            close(saved_stdout);
        }
        else
        {
            pid = fork();
            if(pid == 0)
            {
                if (check_command(head->token, envp) == 0)
                {
                    // ft_putendl_fd_two(head->token, ": command not found", 2);
                    exit(127);
                }
                add_shell_level(my_envp,head,&envp);
                
            }
        }
        
        head = head -> next;
    }
}