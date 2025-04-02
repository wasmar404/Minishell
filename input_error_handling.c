/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:14:57 by schaaban          #+#    #+#             */
/*   Updated: 2025/04/02 08:19:54 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/* check if the first node is a command
 if there is a pipe, check if the node before and the node after is a command
 if there is input redirection, check if the file exists and has permissions
 check if quotes are balanced, if a single q exists in a double q, consider it a character
 if there is an output redirection, check if file name exists, and if it exists check permissions
 cat << : check that parameter exists after <<
 check if command is valid
 
 */
// long long exit_code;
int check_command(char *array,char **envp,t_shell *exitcode)
{
    char *str;
    str = NULL;
    int flag = 0;
    if (array == NULL || envp == NULL) // <-- Add NULL checks
        return (0);
    if(array[0] == '.' && array[1] == '/'  && access(array,X_OK) == 0)
    {
            exitcode -> exit_code = 0;
            return (1);
    
    }
    else if(array[0] == '.' && array[1] == '/'  && access(array,X_OK) != 0)
    {
        exitcode -> exit_code = 127;
        ft_putendl_fd("bash: ./test: No such file or directory",2);
        return (0);
        
    }
    // if(array[0] == '$' && array[1])
    // {
    //     printf("hvcddhblkgjl");
    //     exit_code = 126;
    //     return (0);
    // }
    str = find_path_of_cmd(array,envp,exitcode);
    if(str == NULL)
    {
        flag =1;
    }
    if(flag == 1 && !(strcmp(array, ">") == 0 || strcmp(array, "<") == 0 || 
                       strcmp(array, "<<") == 0 || strcmp(array, ">>") == 0 || strcmp(array,"|") == 0))
    {
            ft_putendl_fd_two("sw_shell: command not found: ",array,2);
            exitcode -> exit_code = 127;
            return(0);
    }
    return (1);
}
int check_if_pipe_is_valid(t_token *head,t_shell *exitcode)
{
    int flag =0;
    t_token *temp = head;
    while(head)
    {
        if(head -> type == PIPE)
        {
            temp = head;
            flag = 0;
            while(temp -> prev != NULL && temp -> prev ->type != PIPE)
            {
                if(temp -> prev -> type == COMMAND)
                    flag = 1;
                 temp = temp -> prev;
            }
            if(check_if_pipe_is_valid_helper(head,exitcode,flag) == 0)
                return (0);
        }
        head = head -> next;
    }
    return(1);
}
int check_if_pipe_is_valid_helper(t_token *head, t_shell *shell,int flag)
{
    if(head -> next == NULL || head -> prev == NULL)
    {
        ft_putendl_fd("bash: syntax error near unexpected token `|'",2);
        shell -> exit_code = 2;
        return(0);
    }
    if(head -> next && head -> next -> type != COMMAND)
    {
        ft_putendl_fd_two(head-> next ->token,": command not found2",2);
        shell -> exit_code = 127;
        return (0);
    }
    if(flag == 0)
    {
        ft_putendl_fd("command not found5848", 2);
        shell -> exit_code = 127;
        return (0);
    }
    return (1);
}
int count_commands(t_token *head)
{
    int count;
    count = 0;
    while(head)
    {
        if(head -> type == COMMAND)
            count ++;
        head = head -> next;
    }
    return (count);
}
int count_redirections(t_token *head)
{
    int redirections_count;
    redirections_count = 0;
    while(head)
    {
        if(head -> type == SOUTPUT_REDIRECTION || head -> type == SINPUT_REDIRECTION || head -> type == SOUTPUT_REDIRECTION || head -> type == HERE_DOC)
            redirections_count ++;
        head = head -> next;
    }
    return (redirections_count);
}
int check_if_file_exists(t_token *head,t_shell *exitcode)
{
    t_token *temp;
    temp = head;
    int count = 0;
    while(head)
    {
        if(head -> type == SINPUT_REDIRECTION)
        {
            // if(head -> next && head -> next -> type != DIRECTORY)
            // {
            //     // printf("bash: no such file or directory: %s\n",head -> next -> token);
            //     ft_putendl_fd_two("bash: no such file or directory: ",head -> next -> token,2);
            //     exit_code = 1;
            //     count ++;
            // }
            if(head -> next == NULL)
            {
                ft_putendl_fd("bash: syntax error near unexpected token `newline'",2);
                exitcode -> exit_code = 2;
                return (0);
            }
            // if(head -> next && head -> next -> type == DIRECTORY)
            // {
            //     if(access(head->next->token,R_OK) == -1)
            //     {
            //         ft_putendl_fd_two("bash: Permission denied: ",head -> next -> token,2);
            //         exit_code = 1;
            //         return (0);
            //     }
            // }
        }
        head = head -> next;
    }
    if(count > 0)
        return (0);
    return (1);

}
int check_sout_redirection(t_token *head,t_shell *exitcode)
{
    while(head)
    {
        if(head -> type == SOUTPUT_REDIRECTION)
        {
            if(head -> next == NULL)
            {
                exitcode -> exit_code = 2;
                ft_putendl_fd("bash: syntax error near unexpected token `newline'",2);
                return (0);
            }
            if(head -> next && head -> next -> type == DIRECTORY)
            {
                if(access(head->next->token,R_OK) == -1)
                {
                    ft_putendl_fd_two("bash: Permission denied: ",head -> next -> token,2);
                    exitcode -> exit_code = 1;
                    return (0);
                }
            }
        }
        head = head -> next;
    }
    return (1);
}
int check_aout_redirection(t_token *head,t_shell *exitcode)
{
    while(head)
    {
        if(head -> type == AOUTPUT_REDIRECTION)
        {
        if(head -> type == AOUTPUT_REDIRECTION && (head -> prev == NULL || head -> next == NULL))
        {
            ft_putendl_fd("bash: syntax error near unexpected token `newline'",2);
            exitcode -> exit_code = 2;
            return (0);
        }
        if(head -> next && head -> next -> type == DIRECTORY)
        {
            if(access(head->next->token,R_OK) == -1)
            {
                ft_putendl_fd_two("bash: Permission denied: ",head -> next -> token,2);
                exitcode -> exit_code = 1;
                return (0);
            }
        }
    }
        head = head -> next;
    }
    return (1);
}
int check_redirections_sequence(t_token *head,t_shell *exitcode)
{
    while(head)
    {
        if(head -> type == SOUTPUT_REDIRECTION || head -> type == AOUTPUT_REDIRECTION
                || head -> type == SINPUT_REDIRECTION || head -> type == HERE_DOC)
        {
            if(head -> next && (head -> next -> type == SOUTPUT_REDIRECTION || head -> next -> type == AOUTPUT_REDIRECTION
                || head -> next -> type == SINPUT_REDIRECTION || head -> next -> type == HERE_DOC || head -> next -> type == PIPE))
            {
                ft_putendl_fd_two("bash: syntax error near unexpected token ",head -> next -> token,2);
                exitcode -> exit_code = 2;
                return (0);
            }
        }
        head = head -> next;
    }
    return (1);
}
int check_here_doc(t_token *head,t_shell *exitcode)
{
    while(head)
    {
        if(head -> type == HERE_DOC)
        {
            if(head -> next == NULL)
            {
                exitcode -> exit_code = 2;
                ft_putendl_fd("bash: syntax error near unexpected token `newline'",2);
                return (0);
            }
        }

        head = head -> next;
    }
    return (1);
}
int  main_quote_check(char *str,t_shell *exitcode)
{
    // int inside_quote = 0;
    // int d_start = 0 ;
    // int s_start =0;
    t_quotes quotes;
    quotes.d_start =0;
    quotes.s_start =0;
    quotes.inside_quote=0;
    int i = 0;
      while(str[i])
      {
         update_quote_status(&quotes,str[i]);
        i++;
      }
      if((quotes.inside_quote) > 0)
      {
        ft_putendl_fd("quote not ft_closed",2);
        exitcode -> exit_code = 1;
            return (0);
      }
      return (1);
}

int check_if_dir_after_redirections(t_token *head,t_shell *exitcode)
{
    struct stat path_stat;
    while(head)
    {
        if(head -> type == SOUTPUT_REDIRECTION || head -> type == AOUTPUT_REDIRECTION
                || head -> type == SINPUT_REDIRECTION)
        {
            if(head && head->next && head -> next -> type == DIRECTORY)
            {
                if (stat(head->next->token, &path_stat) == 0)
                {
                    // Check if it's a directory
                    if (S_ISDIR(path_stat.st_mode))
                    {
                        // Handle the "Is a directory" error
                        ft_putendl_fd("bash: Is a directory", 2);
                        exitcode -> exit_code = 1; // Set exit_code if required globally
                        return (0); // Return 0 to indicate an error
                    }
                }
            }
        }
        head = head -> next;
    }
    return (1);
}
int check_cd_command(t_token *head,t_shell *exitcode)
{
    struct stat path_stat;
    while (head)
    {
        if(head -> type == COMMAND)
        {
            if(head ->next && strcmp(head -> token,"cd") == 0 && (head -> next -> type == WORD))
            {
                exitcode -> exit_code = 1;
                ft_putendl_fd("bash: cd: No such file or directory",2);
                return (0);
            }
        }
        head = head -> next;
    }
    return (1);
    
}
void    ft_putendl_fd_two(char *s,char *str, int fd)
{
    write(fd, s, ft_strlen(s));
    write(fd, str, ft_strlen(str));
    write(fd, "\n", 1);
}
int input_check(t_token *head,char **array,char **envp,t_shell *exitcode)
{
    int i = 0;

    // if(check_command(head -> token,envp) == 0)
    //        return (0);
    if(check_if_pipe_is_valid(head,exitcode) == 0)
        return(0);
    if(check_cd_command(head,exitcode) == 0)
        return (0);
    if(check_redirections_sequence(head,exitcode) == 0)
        return (0);
    if(check_if_dir_after_redirections(head,exitcode) == 0)
        return (0);
    if(check_aout_redirection(head,exitcode) == 0)
        return (0);
    if(check_if_file_exists(head,exitcode) == 0)
        return (0);
    if(check_sout_redirection(head,exitcode) == 0)
        return (0);
    if(check_here_doc(head,exitcode) == 0)
        return (0);
    return(1);
}