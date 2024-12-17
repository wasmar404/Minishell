/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:28:27 by wasmar            #+#    #+#             */
/*   Updated: 2024/12/17 21:07:31 by wasmar           ###   ########.fr       */
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
void main_cd(t_token *head, t_env **my_envp)
{
if(!head->next)
{
    search_and_find_a_type_my_envp(my_envp,"HOME");
    t_env *a = *(my_envp);
    chdir(a->enva);
    return_env_to_beginning(my_envp);
    search_and_find_a_type_my_envp(my_envp,"PWD");
    t_env *new_oldpwd = *(my_envp);
    return_env_to_beginning(my_envp);
    search_and_find_a_type_my_envp(my_envp,"OLDPWD");
    strcpy((*my_envp)->enva,new_oldpwd->enva);
    return_env_to_beginning(my_envp);
    search_and_find_a_type_my_envp(my_envp,"PWD");
    strcpy((*my_envp)->enva,a->enva);
    return_env_to_beginning(my_envp);
    //go back to the home dic 
}
if(head->next && head->next->type ==TILDE)
{
    search_and_find_a_type_my_envp(my_envp,"HOME");
    t_env *a = *(my_envp);
    chdir(a->enva);
    return_env_to_beginning(my_envp);
    search_and_find_a_type_my_envp(my_envp,"PWD");
    t_env *new_oldpwd = *(my_envp);
    return_env_to_beginning(my_envp);
    search_and_find_a_type_my_envp(my_envp,"OLDPWD");
    strcpy((*my_envp)->enva,new_oldpwd->enva);
    return_env_to_beginning(my_envp);
    search_and_find_a_type_my_envp(my_envp,"PWD");
    strcpy((*my_envp)->enva,a->enva);
    return_env_to_beginning(my_envp);
    //go back to the home dic

}
if(head->next && head->next->type == TWO_POINTS)
{
    char cwd[1000];
    char *current_path = getcwd(cwd, sizeof(cwd));
    int i = 0;
    int j = 0;
    while (current_path[i])
    {
        if(current_path[i] == '/')
            j = i;
        i++;
    }
    char *new_path = ft_strndup(current_path,j);
    search_and_find_a_type_my_envp(my_envp,"PWD");
    return_env_to_beginning(my_envp);
    t_env *new_oldpwd = *(my_envp);
    search_and_find_a_type_my_envp(my_envp,"OLDPWD");
    return_env_to_beginning(my_envp);
    strcpy((*my_envp)->enva,new_oldpwd->enva);
    search_and_find_a_type_my_envp(my_envp,"PWD");
    strcpy((*my_envp)->enva,new_path);
    return_env_to_beginning(my_envp);
    chdir(new_path);
    //go back one dir

}
if (head->next && head->next->type == MINUS) {
    // Find and store OLDPWD
    search_and_find_a_type_my_envp(my_envp, "OLDPWD");
    t_env *oldpwd = *my_envp;

    // Change the directory to PWD
    search_and_find_a_type_my_envp(my_envp, "PWD");
    t_env *new_path = *my_envp;
    chdir(new_path->enva);

    // Update OLDPWD to the current directory
    return_env_to_beginning(my_envp);
    search_and_find_a_type_my_envp(my_envp, "OLDPWD");
    strcpy((*my_envp)->enva, new_path->enva);

    // Update PWD to the directory in new_path
    return_env_to_beginning(my_envp);
    search_and_find_a_type_my_envp(my_envp, "PWD");
    strcpy((*my_envp)->enva, oldpwd->enva);

    return_env_to_beginning(my_envp);
}

}