/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:28:27 by wasmar            #+#    #+#             */
/*   Updated: 2025/03/17 20:22:42 by wasmar           ###   ########.fr       */
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

// void cd(t_token *head, t_env **my_envp,t_shell *exitcode)
// {
//         char *a;
//     char *new_oldpwd;
//  if(!(head -> next))
//  {
//         search_and_find_a_type_my_envp(my_envp,"HOME");
//         if((*my_envp))
//         {
//             if((*my_envp))
//                 a = strdup((*my_envp)->enva);
//             if(chdir(a) == -1)
//             {
//                 exitcode -> exit_code = 1;
//                 free (a);
//                 return ;
//             }
//         return_env_to_beginning(my_envp);
//         }
//          else
//         {
//             return;
//         }
//         search_and_find_a_type_my_envp(my_envp,"PWD");
//         if((*my_envp))
//         {
//             new_oldpwd = strdup((*my_envp)->enva);
//             strcpy((*my_envp)->enva,a);
//             return_env_to_beginning(my_envp);
//         }
//         else
//         {
//             return;
//         }
//         search_and_find_a_type_my_envp(my_envp,"OLDPWD");
//         if((*my_envp))
//         {
//             strcpy((*my_envp)->enva,new_oldpwd);
//             return_env_to_beginning(my_envp);
//             free(new_oldpwd);
//         }
//         else
//         {
//             return;
//         }
//         if (!(*my_envp)) 
//         {
            // ft_putendl_fd("cd: HOME not set\n",2);
            // exitcode -> exit_code = 1;
//             return ;
//         }
//         else
//         {
//             return;
//         }
//         free(a);
//     exitcode -> exit_code = 0;
//  }
// }
// void cd_TILDE(t_token *head, t_env **my_envp,t_shell *exitcode)
// {
//     char *a;
//     char *new_oldpwd;
//     if(head->next && head->next->type ==TILDE)
//     {
//         search_and_find_a_type_my_envp(my_envp,"HOME");
//              if((*my_envp))
//         {
//         if((*my_envp))
//             a = strdup((*my_envp)->enva);
//         if(chdir(a) == -1)
//         {
//             exitcode -> exit_code = 1;
//             free (a);
//             return ;
//         }
//         return_env_to_beginning(my_envp);
//         }
//         else
//         {
//             return;
//         }
//         search_and_find_a_type_my_envp(my_envp,"PWD");
//         if((*my_envp))
//         {
//             new_oldpwd = strdup((*my_envp)->enva);
//             strcpy((*my_envp)->enva,a);
//             return_env_to_beginning(my_envp);
//         }
//         else
//         {            return;
//         }
//         search_and_find_a_type_my_envp(my_envp,"OLDPWD");
//         if((*my_envp))
//         {
//             strcpy((*my_envp)->enva,new_oldpwd);
//             return_env_to_beginning(my_envp);
//             free(new_oldpwd);
//         }
//         else
//         {
//             return;
//         }
//         if (!(*my_envp)) 
//         {
//             ft_putendl_fd("cd: HOME not set\n",2);
//             exitcode -> exit_code = 1;
//             return ;
//         }
//         else
//         {
//             return;
//         }
//         free(a);
//     //go back to the home dic 
//      exitcode -> exit_code = 0;
//     } 

// }
// void cd_DIRECTORY(t_token *head, t_env **my_envp, t_shell *exitcode)
// {
//     char *old_pwd;
//     char *new_pwd; 
//     if(head -> next && head -> next -> type == DIRECTORY)
//     {
//         search_and_find_a_type_my_envp(my_envp,"PWD");
//         if((*my_envp))
//         {
//             old_pwd = ft_strdup((*my_envp)-> enva);
//             return_env_to_beginning(my_envp);
//         }
//         else
//         {
//             return;
//         }
//         search_and_find_a_type_my_envp(my_envp,"OLDPWD");
//         if((*my_envp))
//         {
//             strcpy((*my_envp) -> enva, old_pwd);
//             return_env_to_beginning(my_envp);
//             new_pwd = ft_strjoin(old_pwd,"/");
//             new_pwd = ft_strjoin(new_pwd,head -> next -> token);
//         }
//         else
//         {
//             return;
//         }
//         if(chdir(new_pwd) == -1)
//         {
//             exitcode -> exit_code = 1;
//             return ;
//         }
//         search_and_find_a_type_my_envp(my_envp,"PWD");
//         if((*my_envp))
//         {       
//             strcpy((*my_envp) -> enva, new_pwd);
//             return_env_to_beginning(my_envp);
//                     free(old_pwd);
//         free(new_pwd);
//         }
//         else
//         {
//             return;
//         }
//     exitcode -> exit_code = 0;
// } 
 
// }
// void cd_MINUS(t_token *head, t_env **my_envp, t_shell *exitcode)
// {
//     char *oldpwd ;
//     char *new_oldpwd;
//    if (head->next && head->next->type == MINUS) {
//     search_and_find_a_type_my_envp(my_envp, "OLDPWD");
//     if((*my_envp))
//     { 
//         oldpwd = strdup((*my_envp)->enva);
//         chdir(oldpwd);
//         return_env_to_beginning(my_envp);
//     }
//     else
//     {
//         return;
//     }
//     search_and_find_a_type_my_envp(my_envp, "PWD");
//     if((*my_envp))
//     { 
//     new_oldpwd = strdup((*my_envp)->enva);
//     strcpy((*my_envp)->enva,oldpwd);
//     return_env_to_beginning(my_envp);
//         free(oldpwd);

//     }
//     else
//     {
//         return;
//     }
//     search_and_find_a_type_my_envp(my_envp, "OLDPWD");
//     if((*my_envp))
//      { 
//     strcpy((*my_envp)->enva,new_oldpwd);
//     return_env_to_beginning(my_envp);
//     free(new_oldpwd);
//     }
//     else{
//         return;
//     }
// } 
// exitcode -> exit_code = 0;
// }
// void cd_TWO_POINTS(t_token *head, t_env **my_envp,t_shell *exitcode)
// {
//     char cwd[1000];
//     char *current_path;
//     char *new_path;
//     char *new_old;

//     if(head->next && head->next->type == TWO_POINTS)
//     {
//         current_path = getcwd(cwd, sizeof(cwd));
//         int i = 0;
//     int j = 0;
//     while (current_path[i])
//     {
//         if(current_path[i] == '/')
//             j = i;
//         i++;
//     }
//     new_path = ft_strndup(current_path,j);
//     search_and_find_a_type_my_envp(my_envp,"PWD");
//      if((*my_envp))
//      { 
//         new_old = ft_strdup((*my_envp)->enva);
//         strcpy((*my_envp)->enva,new_path);
//         return_env_to_beginning(my_envp);
//      }
//      else
//      {
//         return;
//      }
//     search_and_find_a_type_my_envp(my_envp,"OLDPWD");
//     if((*my_envp))
//      { 
//     strcpy((*my_envp)->enva,new_old);
//     return_env_to_beginning(my_envp);
//     chdir(new_path);
//     free(new_old);
//         free(new_path);
//      }
//     else
//     {
//         return;
//     }
//     //go back one dir
// exitcode -> exit_code = 0;
// }  
// }
// void main_cd(t_token *head, t_env **my_envp, t_shell *exitcode)
// {
//     if(!my_envp || !head)
//     {
//         exitcode -> exit_code = 1;
//         return ;
//     }
//     if(head && head->next && head ->next->next && head -> next -> next -> type == WORD)
//     {
//         ft_putendl_fd("cd: too many arguments",2);
//         exitcode -> exit_code = 1;
//         return ;
//     }
//     cd(head,my_envp,exitcode);
//     cd_DIRECTORY(head,my_envp,exitcode);
//     cd_MINUS(head,my_envp,exitcode);
//     cd_TILDE(head,my_envp,exitcode);
//     cd_TWO_POINTS(head,my_envp,exitcode);
// }