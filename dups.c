/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:55:44 by wasmar            #+#    #+#             */
/*   Updated: 2025/02/03 02:23:20 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


void handle_dups(t_token *head,int *pipefd, int input_fd,int flag);
void check_and_create_file(t_token *head);
void check_back(t_token *head,t_token **current_input,t_token **current_output ,int *flag);
void dups1(t_token *current_input,t_token *current_output,int *pipefd);
void dups2(t_token *current_input,t_token *current_output,int input_fd,t_token *head);
void check_front(t_token *head,t_token **current_input,t_token **current_output ,int *flag);

void super_complicated_handle_dups(t_token *head,int *pipefd, int input_fd,int flag)
{
    t_token *current = head;
    t_token *current1 = head;
    t_token *current_input =NULL;
    t_token *current_output =NULL;
    int flag1= 0;
    if (input_fd != STDIN_FILENO)
    {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    check_back(head,&current_input,&current_output,&flag1);
    check_front(current,&current_input,&current_output,&flag1);
    dups1(current_input,current_output,pipefd);
    dups2(current1,current_output,input_fd,head);
    if(flag == 1)
    {
        close(pipefd[0]);
        close(pipefd[1]);
    }
}
void check_and_create_file(t_token *head)
{
    int fd;
    fd = 0;
    if(head->type == SOUTPUT_REDIRECTION)
    {

            
         if (head->next->type == DIRECTORY && access(head->next->token, W_OK) == -1)
        {
            int dev_null = open("/dev/null", O_WRONLY);
            dup2(dev_null, STDOUT_FILENO);
            return;
        }  
        fd = open(head->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd,1);
        close(fd);
    }
    else if(head->type == AOUTPUT_REDIRECTION)
    {

         if (head->next->type == DIRECTORY && access(head->next->token, W_OK) == -1)
        {
            int dev_null = open("/dev/null", O_WRONLY);
            dup2(dev_null, STDOUT_FILENO);
            return;
        }
        fd = open(head->next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd,1);
        close(fd);
    }
}
void check_front(t_token *head,t_token **current_input,t_token **current_output ,int *flag)
{
   t_token *temp = head->next;
    while(temp != NULL && temp->type != COMMAND)
    {
            if((temp->type == HERE_DOC))
            {
                heredoc_dup(temp);
                break;
            }
            temp =temp ->next;
    }
    head = head ->next;
    while(head != NULL  && head -> type != COMMAND)
    {

        if((head->type == AOUTPUT_REDIRECTION || head->type == SOUTPUT_REDIRECTION) && (*flag == 0))
        {
            (*current_output) = head;
            check_and_create_file(head);            
        }
       else if (head->type == PIPE && ((!(*current_output) || ((*current_output)->type != AOUTPUT_REDIRECTION && (*current_output)->type != SOUTPUT_REDIRECTION))) && (*flag == 0))
        {
            (*current_output) = head;
            break;
        }
        else if((head->type == SINPUT_REDIRECTION))
		{
            (*current_input) = head;
		}
        head = head ->next;
    }
}
void check_back(t_token *head,t_token **current_input,t_token **current_output ,int *flag)
{
    while(head && head -> type != PIPE)
    {
        if(head ->type == SINPUT_REDIRECTION || head ->type == PIPE || head ->type ==HERE_DOC)
        {
            (*current_input) = head;
        }
        if(head->type == AOUTPUT_REDIRECTION || head ->type == SOUTPUT_REDIRECTION)
        {
            (*current_output) = head;
            check_and_create_file(head);
            (*flag)++;
        }
        head = head -> prev;
    }
}
void dups2(t_token *current_input,t_token *current_output,int input_fd,t_token *head)
{
    int fd;
    if(current_input && current_input->type == PIPE)
    {
        dup2(input_fd,0);
        close(input_fd);
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