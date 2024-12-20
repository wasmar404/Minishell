/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:28:27 by wasmar            #+#    #+#             */
/*   Updated: 2024/12/18 10:26:07 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

void search_and_find_a_type_my_envp(t_env **envp,char *to_find)
{
    while((*envp) != NULL)
    {
        if(ft_strcmp(to_find,(*envp)->type) == 0)
        {
            // return(envp);
            break;
        }
        (*envp) = (*envp)->next;
    }
}
void return_env_to_beginning(t_env **my_envp)
{
    while((*my_envp)->prev)
    {
        (*my_envp) = (*my_envp) ->prev;
    }
}
void cd(t_token *head, t_env **my_envp)
{
        char *a;
    char *new_oldpwd;
    if(head->next && head->next->type ==TILDE)
    {
        search_and_find_a_type_my_envp(my_envp,"HOME");
        a = strdup((*my_envp)->enva);
        chdir(a);
        return_env_to_beginning(my_envp);
        search_and_find_a_type_my_envp(my_envp,"PWD");
        new_oldpwd = strdup((*my_envp)->enva);
        strcpy((*my_envp)->enva,a);
        return_env_to_beginning(my_envp);
        search_and_find_a_type_my_envp(my_envp,"OLDPWD");
        strcpy((*my_envp)->enva,new_oldpwd);
        return_env_to_beginning(my_envp);
        free(a);
        free(new_oldpwd);
}
}
void cd_TILDE(t_token *head, t_env **my_envp)
{
    char *a;
    char *new_oldpwd;
    if(head->next && head->next->type ==TILDE)
    {
        search_and_find_a_type_my_envp(my_envp,"HOME");
        a = strdup((*my_envp)->enva);
        chdir(a);
        return_env_to_beginning(my_envp);
        search_and_find_a_type_my_envp(my_envp,"PWD");
        new_oldpwd = strdup((*my_envp)->enva);
        strcpy((*my_envp)->enva,a);
        return_env_to_beginning(my_envp);
        search_and_find_a_type_my_envp(my_envp,"OLDPWD");
        strcpy((*my_envp)->enva,new_oldpwd);
        return_env_to_beginning(my_envp);
        free(a);
        free(new_oldpwd);
    //go back to the home dic 
    } 
}
void cd_DIRECTORY(t_token *head, t_env **my_envp)
{
    char *old_pwd;
    char *new_pwd; 
  if(head -> next && head -> next -> type == DIRECTORY)
{
    search_and_find_a_type_my_envp(my_envp,"PWD");
    old_pwd = ft_strdup((*my_envp)-> enva);
    return_env_to_beginning(my_envp);
    search_and_find_a_type_my_envp(my_envp,"OLDPWD");
    strcpy((*my_envp) -> enva, old_pwd);
    return_env_to_beginning(my_envp);
    new_pwd = ft_strjoin(old_pwd,"/");
    new_pwd = ft_strjoin(new_pwd,head -> next -> token);
    chdir(new_pwd);
    search_and_find_a_type_my_envp(my_envp,"PWD");
    strcpy((*my_envp) -> enva, new_pwd);
    return_env_to_beginning(my_envp);
    free(old_pwd);
    free(new_pwd);
}  }
void cd_MINUS(t_token *head, t_env **my_envp)
{
    char *oldpwd ;
    char *new_oldpwd;
   if (head->next && head->next->type == MINUS) {
    search_and_find_a_type_my_envp(my_envp, "OLDPWD");
    oldpwd = strdup((*my_envp)->enva);
    chdir(oldpwd);
    return_env_to_beginning(my_envp);
    
    search_and_find_a_type_my_envp(my_envp, "PWD");
    new_oldpwd = strdup((*my_envp)->enva);
    strcpy((*my_envp)->enva,oldpwd);
    return_env_to_beginning(my_envp);
    
    search_and_find_a_type_my_envp(my_envp, "OLDPWD");
    strcpy((*my_envp)->enva,new_oldpwd);
    return_env_to_beginning(my_envp);
    free(oldpwd);
    free(new_oldpwd);
} 
}
void cd_TWO_POINTS(t_token *head, t_env **my_envp)
{
    char cwd[1000];
    char *current_path;
    char *new_path;
    char *new_old;

    if(head->next && head->next->type == TWO_POINTS)
    {
        current_path = getcwd(cwd, sizeof(cwd));
        int i = 0;
    int j = 0;
    while (current_path[i])
    {
        if(current_path[i] == '/')
            j = i;
        i++;
    }
    new_path = ft_strndup(current_path,j);
    search_and_find_a_type_my_envp(my_envp,"PWD");
    new_old = ft_strdup((*my_envp)->enva);
    strcpy((*my_envp)->enva,new_path);
    return_env_to_beginning(my_envp);
    search_and_find_a_type_my_envp(my_envp,"OLDPWD");
    strcpy((*my_envp)->enva,new_old);
    return_env_to_beginning(my_envp);
    chdir(new_path);
    free(new_old);
    free(new_path);
    //go back one dir

}  
}
void main_cd(t_token *head, t_env **my_envp)
{
    cd(head,my_envp);
    cd_DIRECTORY(head,my_envp);
    cd_MINUS(head,my_envp);
    cd_TILDE(head,my_envp);
    cd_TWO_POINTS(head,my_envp);
}