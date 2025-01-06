// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   dollar.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/30 11:00:31 by wasmar            #+#    #+#             */
// /*   Updated: 2025/01/04 11:40:01 by wasmar           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "header.h"
// int	check_dollar2(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
// int	check_dollar3(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] != ':')
// 		{
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
// int dollar_count(char *str)
// {
//     int	i;

// 	i = 0;
//     int count = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] != ':')
//             count++;
// 		i++;
// 	}

//     // printf("count: %d\n",count);
// 	return (count);
// }
// int	check_dollar_pos_fixed(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] != ':') // added the rest of the stuff
// 		{
// 			return (i);
// 		}
// 		i++;
// 	}
// 	return (-42);
// }
// int check_dollar_plus1(char *str,t_token **head)
// {
//     int i;
//     int j =0;
//     int x= 0;
//     char *new = NULL;
//     char *output;
//     char *new_string = NULL;
//     i = check_dollar_pos_fixed(str);
//     if(str[i+1] && (str[i+1] == '"' || str[i+1] == '\''))
//     {
//         new = strdup(str+i+1);
//         new_string = malloc(strlen(str));//strlen fixxxxxxxxxxxxxxxxxxxx!!!!!!!!!!!!!!!!!
//         while((*head)->token[j] && (*head)->token[j] != '$')
//         {
//             new_string[x] = (*head)->token[j];
//             x++;
//             j++;
//         }
//         j = 0;
//         while(new[j])
//         {
//             new_string[x] = new[j];
//             x++;
//             j++;
//         }
//                     new_string[x] = '\0';
//         (*head)->token = malloc(strlen(str));
//         strcpy((*head)->token,new_string);
//         return(1);
//     }
//     else if(str[i+1] && (str[i+1] >= '0' && str[i+1]<= '9'))
//     {
//         new = strdup(str+i+2);
//         new_string = malloc(strlen(str)+1);//strlen fixxxxxxxxxxxxxxxxxxxx!!!!!!!!!!!!!!!!!
//         while((*head)->token[j] && (*head)->token[j] != '$')
//         {
//             new_string[x] = (*head)->token[j];
//             x++;
//             j++;
//         }
//         j = 0;
//         while(new[j])
//         {
//             new_string[x] = new[j];
//             x++;
//             j++;
//         }
//         new_string[x] = '\0';
//         (*head)->token = malloc(strlen(str)+1);
//         strcpy((*head)->token,new_string);
//         return(1);
//     }
//     else if(str[i+1] && !((str[i+1] >='a' && str[i+1] <= 'z') || (str[i+1] >='A' && str[i+1] <= 'Z') || (str[i+1] >='0' && str[i+1] <= '9') || str[i+1] == '_' ))
//     {
//         new = strdup(str+i+2);
//         if(dollar_main_char((*head)->token) != NULL)
//         {
//             output = dollar_main_char((*head)->token);
//             new_string = malloc(strlen(output)+strlen((*head)->token)-strlen(new)+1);
//             while((*head)->token[j] && j != check_dollar_pos_fixed(str)+2)
//             {
//                 new_string[x] = (*head)->token[j];
//                 x++;
//                 j++;
//             }
//             j = 0;
//             while(output[j])
//             {
//                 new_string[x] = output[j];
//                 x++;
//                 j++;
//             }
//             new_string[x] = '\0';
//             (*head)->token = malloc(strlen(new_string)+1);
//             strcpy((*head)->token,new_string);
//             return(1);
//         }
//         if(dollar_main_char((*head)->token) == NULL)
//             return(1);
//     }
//     return(0);
    
// }
// char *dollar_main_char(char *str)
// {
//     int i = 0;
//     char *new_string;
//     if(check_dollar2(str) == 0)
//     {
//         return(NULL);
//     }
//     if(check_dollar_plus1_char(&str) != NULL)
//     {
//         new_string = check_dollar_plus1_char(&str);
//         return(new_string);
//     }
//     // else
//     // {
//     //     new_string = strdup(str);
//     // }
//     //expand
// }
// int	expand_or_not(t_token *head)
// {
// 	int	i;

// 	i = 0;
// 	while (head->token[i])
// 	{
// 		if (head->token[i] == '"')
// 		{
// 			return (1);
// 		}
// 		if (head->token[i] == '\'')
// 		{
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }
// void main_dollar(t_token **head,t_env *envp)
// {
//     (void)envp;
//     int i;
//     i = 0;
//     // int count = 0;
//     while((*head))
//     {
//         // count = dollar_count((*head)->token);
//        while( dollar_count((*head)->token) >0 )
//        {
      
//             if(check_dollar_plus1((*head)->token,head) == 1)
//             {
//                 continue;
//             }
//             // if (expand_or_not((*head)))
//             // {
//                              expand_dollar1(head,envp);
//             // }
//             // else
//             // {
//             //     break;
//             // }
            
//             //  break;
//             i++;
//         }
//         (*head) = (*head) -> next;
        
//     }
// }


// char * check_dollar_plus1_char(char **str)
// {
//     int i;
//     int j =0;
//     int x= 0;
//     char *new = NULL;
//     char *new_string = NULL;
//     char *output = NULL;
//     i = check_dollar_pos_fixed((*str));
//     if((*str)[i+1] && ((*str)[i+1] == '"' || (*str)[i+1] == '\''))
//     {
//         new = strdup((*str)+i+1);
//          new_string = malloc(strlen((*str)));//strlen fixxxxxxxxxxxxxxxxxxxx!!!!!!!!!!!!!!!!!
//         while((*str)[j] && (*str)[j] != '$')
//         {
//             new_string[x] = (*str)[j];
//             x++;
//             j++;
//         }
//          j = 0;
//         while(new[j])
//         {
//             new_string[x] = new[j];
//             x++;
//             j++;
//         }
//         return(new_string);
//     }
//     else if(str[i+1] && ((*str)[i+1] >= '0' && (*str)[i+1]<= '9'))
//     {
//         new = strdup((*str)+i+2);
//          new_string = malloc(strlen((*str)));//strlen fixxxxxxxxxxxxxxxxxxxx!!!!!!!!!!!!!!!!!
//         while((*str)[j] && (*str)[j] != '$')
//         {
//             new_string[x] = (*str)[j];
//             x++;
//             j++;
//         }
//          j = 0;
//         while(new[j])
//         {
//             new_string[x] = new[j];
//             x++;
//             j++;
//         }
//         return(new_string);
       
//     }
//   else if(str[i+1] && !(((*str)[i+1] >='a' && (*str)[i+1] <= 'z') || ((*str)[i+1] >='A' && (*str)[i+1] <= 'Z') || ((*str)[i+1] >='0' && (*str)[i+1] <= '9') || (*str)[i+1] == '_' ))
//     {
//         new = strdup((*str)+i+2);
//        if(dollar_main_char((*str)) != NULL)
//        {
//              output = dollar_main_char((*str));
//              new_string = malloc(strlen(output)+strlen((*str))-strlen(new));
//             while((*str)[j]&& j != check_dollar_pos_fixed((*str)+2))
//             {
//                 new_string[x] = (*str)[j];
//                 x++;
//                 j++;
//             }
//              j = 0;
//             while(output[j])
//             {
//                 new_string[x] = output[j];
//                 x++;
//                 j++;
//             }
//             return(new_string);
//        }
//      }
//     return(NULL);
    
// }
// int find_end_variable(char *str)
// {
//     int i = check_dollar_pos_fixed(str);
//     i++;
// 	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
// 			|| (str[i] >= 'A' && str[i] <= 'Z')
// 			|| (str[i] >= '0' && str[i] <= '9')
// 			|| str[i] == '_'))
// 	{
// 		i++;
// 	}
//     return(i);
    
// }
// char	*fill_array(int len, int start, int end, t_token **head, t_env *enva)
// {
// 	int		x;
// 	int		y;
// 	char	*new;

// 	x = 0;
// 	y = 0;
// 	new = NULL;
// 	new = malloc(len + 1);
// 	while (x < len && y < start)
// 	{
// 		new[x] = (*head)->token[y];
// 		x++;
// 		y++;
// 	}
// 	if (enva)
// 	{
// 		y = 0;
// 		while (x < len && enva->enva[y])
// 		{
// 			new[x] = enva->enva[y];
// 			x++;
// 			y++;
// 		}
// 	}
// 	y = end;
// 	// y++;
// 	while (x < len && (*head)->token[y])
// 	{
// 		new[x] = (*head)->token[y];
// 		x++;
// 		y++;
// 	}
// 	new[x] = '\0';
// 	return (new);
// }
// void expand_dollar1(t_token **head,t_env *envp_linked)
// {
//     //   printf("i am in expand");
//     int end;
//     int start;
//     int len = 0;
//     char *find = NULL;
//     t_env *to_replace;
//     char *expanded = NULL;
//     start = check_dollar_pos_fixed((*head)->token);
//     //  printf("head token: %s\n",(*head)->token);
// //  printf("start: %d\n",start);
//     end = find_end_variable((*head)->token);
//     // printf("end: %d\n",end);
//     find = ft_strndup((*head)->token+start+1,end-start-1);//strlen!!!!!!!!!!!!!
//     //  printf("find: %s\n",find);
//     to_replace = search_and_find_a_type_my_envpp(envp_linked,find);
//     if(to_replace != NULL)
//     {
//         len = strlen((*head)->token) +strlen(to_replace->enva)-strlen(find);
//        expanded =  fill_array(len,start,end,head,to_replace);
//        (*head)->token = malloc(len);
//        strcpy((*head)->token,expanded);
//     }
//     else{
//         len = strlen((*head)->token)-strlen(find);
//         expanded =  fill_array(len,start,end,head,to_replace);
//        (*head)->token = malloc(len);
//        strcpy((*head)->token,expanded); 
//     }

// }

