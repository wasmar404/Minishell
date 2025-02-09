/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:49:56 by schaaban          #+#    #+#             */
/*   Updated: 2025/02/09 11:32:56 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int main(int ac, char **av, char **envp)
{
    char    *input =NULL;
    t_env   *head;
    char    **my_envp;
    (void)ac;
    (void)av;
    head = env_to_linked_list(envp);
    my_envp = env_to_array(head);
    main_signal();

    while (1)
    {
        input = readline("sw_shell> ");
     if (input == NULL) 
            break;  
            
        if (*input) {
            add_history(input);
            main_helper(input, my_envp, &head);
        }

        free(input);
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
void print_list(t_token *head)
{
    while(head)
    {
        printf("\"%s\"%d\n",head->token,head->type);
        // fflush(stdout);
        head = head ->next;
    }
}
void free_doubly_linked_list(t_token *head) {
    t_token *temp;

    while (head != NULL) {
        temp = head;        
        head = head->next;
        free(temp->token); 
        free(temp);
    }
}
void check_program()
{
    
}
int pipe_count_array(char **str)
{
    int i;
    int count = 0;
    i = 0;
    while(str[i])
    {
        if(strcmp(str[i],"|") == 0)
            count ++;
        i ++;  
    }
    return (count);
}
void    main_helper(char *input, char **envp,t_env **env_linked)
{
    char    **splitted_input;
    t_token *head;
    if (check_if_null(input) == 0)
        return ;
    if (strcmp(input, "history -c") == 0)
    {
            rl_clear_history(); 
            return ;
    }
    if(main_quote_check(input) == 0)
        return ;
    splitted_input = token_split(input);
    head = input_to_linked_listt(*env_linked,splitted_input,envp);
//    print_list(head);
    //(void)env_linked;
    // printf("\n\n\n\n");
    // replace_exit_code(head);
    if(input_check(head,splitted_input,envp) == 0)
        return ;
    if(pipe_count_array(splitted_input) == 0)
    {
        if (check_command(head->token, envp) == 0)
        {
            return ;
        }
    }
    // main_error1(head);
     complicated_execute(env_linked, head, envp);

     free_doubly_linked_list(head);
     free_array(splitted_input);
}

void find_a_node_move_pointer(t_token **head,int i)
{
    while(*head)
    {
        if((*head) -> node_count == i)
        {
            break;
        }
        (*head) = (*head)->next;
    }
}

int pipe_count(t_token *head)
{
    int pipes;
    pipes = 0;
    while(head != NULL)
    {
        if(head -> type == PIPE)//|| head->type == AOUTPUT_REDIRECTION)
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
            break;  
        }
        current_command[i]=strdup(temp->token);
         i++;
         temp = temp ->  next;
    }
    current_command[i]= NULL;
    return(current_command);
}


void here_doc_first(char *s,t_token *head,int fd)
{
    char *input;
    while(1)
    {
        input = readline("> ");
        if(strcmp(s,input) == 0)
        {
            break;
        }

        write(fd,input,ft_strlenn(input));
         write(fd,"\n",1);
    }
    // if(head -> next -> next)
    // {
    //     printf("%s : command not found\n",head -> next -> next -> token);
    //     exit_code = 127;
    // }
}
void heredoc_dup(t_token *head)
{
    int fd = 0;
    if(head && head->type == HERE_DOC)
    {
        fd = open("temp", O_WRONLY | O_CREAT | O_APPEND , 0644);
        // heredoc(head->next->token,fd);
        here_doc_first(head -> next -> token,head,fd);
        close(fd);
        fd = open("temp",O_RDONLY);
        // dup2(fd,0);
        close(fd);
        unlink("temp");
    }
}
void s_out_redirection(t_token *head)
{
    int fd;
    fd = 0;
    if(head && head -> type == SOUTPUT_REDIRECTION)
    {
        fd = open(head ->next -> token, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        close(fd);
    }
}
void a_out_redirection(t_token *head)
{
    int fd;
    fd = 0;
    if(head && head -> type == AOUTPUT_REDIRECTION)
    {
        fd = open(head -> next -> token, O_CREAT | O_WRONLY | O_APPEND, 0644);
        close (fd);
    }
}
int command_exists(t_token *head)
{
    while(head)
    {
        if(head -> type == COMMAND)
            return(1);
        head = head ->next;
    }
    return(0);
}
void    complicated_execute(t_env **my_envp, t_token *head, char *envp1[])
{
    int     pipefd[2];
    int status;
     char **envp;
    int input_fd;
    (void)envp1;
    input_fd = STDIN_FILENO;
    t_token *temp;
    pid_t pid ;
    t_token *current = head;
    int saved_stdin=dup(STDIN_FILENO);
    int saved_stdout=dup(STDOUT_FILENO);
    int flag = 0;
    int flag20 = 0;

    if(strcmp(current -> token, "exit") == 0)
    {
        exit_command(current);
    }

    while (current != NULL)
    { 
        envp = env_to_array(*my_envp);
        if(command_exists(head) == 0)
        {
            if(current ->type == HERE_DOC)
            heredoc_dup(current);
        else if(current -> type == SOUTPUT_REDIRECTION)
            s_out_redirection(current);
         else if(current -> type == AOUTPUT_REDIRECTION)
            a_out_redirection(current);
        }

        
        if (current->type == COMMAND)
         {
            flag =0;
            temp = current->next;
            while(temp && temp->type != COMMAND)
            {
                if(temp->type == PIPE)
                {
                    if (pipe(pipefd) == -1)
                    {
                        perror("pipe failed");
                        exit(EXIT_FAILURE);
                    }
                    flag++;
                    break;
                }
                else{
                    pipefd[0]=-1;
                    pipefd[1]=-1;
                }
                temp = temp -> next;
            }
            
            if(pipe_count(head) == 0 && ((strcmp(current->token, "env") == 0) || (strcmp(current -> token, "echo") == 0) ||
                    (strcmp(current -> token, "cd") == 0) || (strcmp(current -> token, "pwd") == 0) || (strcmp(current -> token,"export") == 0) || (strcmp(current -> token,"unset") == 0) || (strcmp(current -> token,"exit") == 0)) )
            {
                flag20 = 1;
                run_built_ins(current,my_envp,pipefd,input_fd,0,flag);
                dup2(saved_stdin,STDIN_FILENO);
                dup2(saved_stdout,STDOUT_FILENO);
                close(saved_stdin);
                close(saved_stdout);
            }
            else{
            pid = fork();
            if (pid == 0)
            {
           
                // flag20 = 1;
                if (check_command(current->token, envp) == 0)
                {
                    // ft_putendl_fd_two(current->token, ": command not found", 2);
                    exit(127);
                }
                add_shell_level(my_envp,current,&envp);
                run_command_helper(current,envp,my_envp,pipefd,input_fd,array_complicated_execute(current),flag);
                
                // exit(exit_code);
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
         if(flag==  1)
         close(pipefd[1]);
         }
         free_array(envp);
        current = current->next;
    
    }
    // if(flag20 == 0)
    // {
    //     while (wait(&status) > 0);
    //      exit_code  = status;
    // }
    if (flag20 == 0)
    {
        while (wait(&status) > 0);
        if (WIFEXITED(status)) // Check if the child exited normally
        {
            exit_code = WEXITSTATUS(status); // Extract the exit code
        }
        else if (WIFSIGNALED(status)) // Check if the child was terminated by a signal
        {
            exit_code = 128 + WTERMSIG(status); // Set exit code to 128 + signal number
        }
    }
    // free_doubly_linked_list(current);
}
void change_value_in_envp(t_env *my_envp,char *new_value)
{
        char *new_all;
          my_envp->enva = ft_strdup(new_value);
          if(my_envp ->equal == true)
          {
            new_all = ft_strjoin(my_envp->type,"=");
            my_envp->all = ft_strjoin(new_all,my_envp->enva);
          }
          else
          {
            my_envp->all = ft_strjoin(my_envp->type,my_envp->enva);
          }

}
void add_shell_level(t_env **my_envp,t_token *head,char ***envp)
{
                  if (strcmp(head->token, "./minishell") == 0 || strcmp(head->token, "minishell")  == 0|| strcmp(head->token, "bash") == 0)
                    {
                         search_and_find_a_type_my_envp((my_envp), "SHLVL");
                        
                        if ( (*my_envp)->enva)
                        {
                            int shell = atoi((*my_envp)->enva);
                            shell++;
                            char *a = ft_itoa(shell);
                            (*my_envp)->enva = ft_strdup(a);
                            change_value_in_envp((*my_envp),a);
                                     return_env_to_beginning(my_envp);
                              
                                    (*envp) = env_to_array(*my_envp);
                        }
                    }
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
void run_built_ins(t_token *head, t_env **my_envp,int *pipefd,int input_fd,int flag,int flag2)
{
    t_env *env_copy = (*my_envp);//so the var  my_envp does not become null 
    super_complicated_handle_dups(head,pipefd,input_fd,flag2);
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
            exit_code = 0;
            return;

        }
        if(invalid_option(head) == 0)
        {
            exit_code = 1;
            return ;
        }
        main_unset1(my_envp,head -> next -> token);
    }
    if(flag == 1)
        exit(EXIT_SUCCESS);

}
void external_commands(t_token *head,char **envp, t_env *my_envp,int *pipefd,int input_fd,char **current_command,int flag)
{
    if(find_var_name_return((my_envp),"PATH"))
    {
        (void)my_envp;
             char   *path;
            super_complicated_handle_dups(head,pipefd,input_fd,flag);
            path = find_path_of_cmd(head->token, envp);
            if (execve(path, current_command, envp) == -1)
                printf("execve failed");
            exit(EXIT_SUCCESS);
    }
}
int path_exists(char **envp)
{
    int i = 0;
    while(envp[i])
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
            return (1);
        i ++;
    }
    return (0);
}
void  run_command_helper(t_token *head,char **envp, t_env **my_envp,int *pipefd,int input_fd,char **current_command,int flag)
{
        if(path_exists(envp) == 1)
        {
            if ((strcmp(head->token, "env") == 0) || (strcmp(head -> token, "echo") == 0) || (strcmp(head -> token, "cd") == 0) || (strcmp(head -> token, "pwd") == 0))
                run_built_ins(head,my_envp,pipefd,input_fd,1,flag);
            else if((strcmp(head -> token, "export") == 0) || (strcmp(head -> token, "unset") == 0) || (strcmp(head -> token, "exit") == 0))
                run_built_ins(head,my_envp,pipefd,input_fd,1,flag);
            else
                external_commands(head,envp,(*my_envp),pipefd,input_fd,current_command,flag);
        }
        else
        {
            exit_code = 127;
            // ft_putendl_fd("bash: No such file or directory",2);
            // close(STDIN_FILENO);
            // exit(exit_code);
        }
}
void heredoc(char *str, int fd)
{
    char *input;
    while (1)
    {
        input = readline("> ");
        if (strcmp(str, input) == 0)
        {
            free(input);
            break;
        }
        write(fd, input, strlen(input));
        write(fd, "\n", 1);
        free(input);
    }
}

