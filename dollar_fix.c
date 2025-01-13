/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_fix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:37:55 by wasmar            #+#    #+#             */
/*   Updated: 2025/01/07 12:45:17 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
char *create_array_till_dollar(t_token *head,int index);
int find_dollar_pos1(char *str);
int find_end_variable(char *str,int j);
void check_quotes_status_and_update(int *inside_quote, int *d_start,int *d_end, int *s_start,int *s_end , char c);
int is_num_or_char(char c);
void check_quotes_till_end(char *str,int *inside_quote, int *d_start,int *d_end, int *s_start,int *s_end,int start,int end);
char *check_char_after_dollar(char *str, int inside_quote,t_env *envp);
void expand_and_replace(t_token **head,char *str, int end);
void main_dollar(t_token **head,t_env *env)
{
    int i = 0;
    char *str = NULL;
    int end = 0;
    char *to_expand = NULL;
    int start = 0;
    char *expanded;
    int len = 0;
    int inside_quote = 0; // 1 for "" and 2 for ' and 0 i am outside
    int d_start = 0;
    int d_end = 0;
    int s_start = 0;
    int s_end = 0;
    while((*head))
    {
        i = 0;
        str = NULL;
        while((*head)->token[i])
        {
            check_quotes_status_and_update(&inside_quote,&d_start,&d_end,&s_start,&s_end,(*head)->token[i]);
            if((*head)->token[i] == '$')
            {
               str = create_array_till_dollar(*head,i);
            //    printf("str: \"%s\"\n",str);
               start = i;
               end = find_end_variable((*head)->token,i);
               to_expand = strndup((*head)->token+start,end -start);
                expanded = check_char_after_dollar(to_expand,inside_quote,env);
                // printf("expand: %s\n",to_expand);
                // printf("inside%d\n",inside_quote);
                if(expanded == NULL&& (inside_quote == 0 || inside_quote == 1))
                {
                    expand_and_replace(head,str,end);
                     i = strlen(str) -1;
                }
                else if(expanded)
                {
                    char *temp = ft_strjoin(str,expanded);
                    free(str);
                    str = temp;
                    free(to_expand);
                    free(expanded);
                     expand_and_replace(head,str,end);
                    // printf("head: %s\n",(*head)->token);
                    i = strlen(str)-1 ;
                    
                }
                else
                {
                    i = end;
                }
             check_quotes_till_end((*head)->token,&inside_quote,&d_start,&d_end,&s_start,&s_end,start,end);

            }
            i++;
        }
        (*head) = (*head) ->next;
    }
    
}
void expand_and_replace(t_token **head,char *str, int end)
{
    if(!str[0])
    {
            (*head) -> token = "";
            return;
    }
    char *s;
    int i = 0;
    int x = 0;
    s = strdup((*head) -> token + end);
    int len = strlen(str) + strlen(s);
    (*head) -> token = malloc(len + 1);
    while(str[i])
    {
        (*head) -> token[x] = str[i];
        i ++;
        x ++;
    }
    i = 0;
    while(s[i])
    {
        (*head)->token[x] = s[i];
        i ++;
        x ++;
    }
    (*head)->token[x] = '\0';

}
void check_quotes_till_end(char *str,int *inside_quote, int *d_start,int *d_end, int *s_start,int *s_end,int start,int end)
{
    int i = start;
    while(i <= end)
    {
        check_quotes_status_and_update(inside_quote,d_start,d_end,s_start,s_end,str[i]); 
        i++;
    }
}
char *create_array_till_dollar(t_token *head,int index)
{
    char * new_string;
    int i;
    i = 0;
    new_string = NULL;
    new_string = malloc(index+1);
    while(i < index)
    {
        new_string[i] = head->token[i];
        i++;
    }
    new_string[i] = '\0';
    return(new_string);
}
int find_dollar_pos11(char *str, int j)
{
    int i = j;
    while(str[i])
    {
        if(str[i] == '$')
            return(i);
        i++;
    }
    return(-42);
}
int find_end_variable(char *str,int j)
{
    // printf("str: %s",str);
    int i = find_dollar_pos11(str,j);
    i++;
    // printf("start : %d\n",i);
    if( str[i] == '\"' || str[i] == '\'')
    {
        return(i+1);
    }
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| str[i] == '_' ))
	{
		i++;
	}
        // printf("end : %d\n",i);
    return(i);
    
}
int find_dollar_pos1(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == '$')
            return(i);
        i++;
    }
    return(-42);
}

void check_quotes_status_and_update(int *inside_quote, int *d_start,int *d_end, int *s_start,int *s_end , char c)
{
     if ((c == '"' || c == '\'') && (*inside_quote) == 0)
            {
               if(c == '"')
               {
                    (*inside_quote) = 1;
                    (*d_start) = 1;
               }
               if(c == '\'')
               {
                    (*inside_quote) = 2;
                    (*s_start) = 1;
               }
            }
            else if  ((c == '"' || c == '\'') && ((*inside_quote) == 1 || (*inside_quote) == 2))
            {
                 if(c == '"' && d_start == 1)
               {
                    (*inside_quote) = 0;
                    (*d_end) = 1;
               }
            
               if(c == '\'' && s_start == 1)
               {
                    (*inside_quote) = 0;
                    (*s_end) = 1;
               }
            }
}
t_env	*search_and_find_a_type_my_envpp(t_env *envp, char *to_find)
{
	while ((envp) != NULL)
	{
		if (ft_strcmp(to_find, (envp)->type) == 0)
		{
			return (envp);
		}
		(envp) = (envp)->next;
	}
	return (NULL);
}
char *expand_dollar(char *str,t_env *envp)
{
    char *find;
    find = strdup(str+1);
    t_env *to_replace;
    char *new_string = NULL;
    
    to_replace = search_and_find_a_type_my_envpp(envp,find);
    
    if(to_replace != NULL)
    {
        new_string = strdup(to_replace -> enva);
    }
    return(new_string);
    
}
char *check_char_after_dollar(char *str, int inside_quote,t_env *envp)
{
    char *new_string = NULL;
    // printf("str: \"%s\" %d\n",str,inside_quote);
    // printf("\n%c\n",str[0]);
     if(str[0] == '$' && (str[1] == '"' || str[1] == '\'') && (inside_quote == 0))
    {
        new_string = strdup(str+1);
    }
    else if(str[0] == '$' && (str[1] >= '0' && str[1] <= '9') && (inside_quote == 0 || inside_quote ==1))
    {
        new_string = strdup(str+2);
    }
    else if((is_num_or_char(str[1]) == 0 && (str[1] != '_')) && str[0] == '$' && (inside_quote == 0 || inside_quote ==1))
    {
        new_string = strdup(str);
    }
    else if((is_num_or_char(str[1]) == 1 || (str[1] == '_')) && str[0] == '$' && (inside_quote == 0 || inside_quote ==1))
     {//check ffirst charr
        new_string = expand_dollar(str,envp);
     }
    //  printf("null1");
    return (new_string);
}
int is_num_or_char(char c)
{
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
    {
        return(1);
    }
    return (0);
}