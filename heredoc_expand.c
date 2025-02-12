// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   heredoc_expand.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/10 12:23:12 by schaaban          #+#    #+#             */
// /*   Updated: 2025/02/10 13:59:25 by schaaban         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

 #include "header.h"
// void remove_quotes_and_replace_h(char *str,int start)
// {
// 	int end = 0;
// 	char *new = NULL;
// 	int len =0;
// 	end = find_end_of_quotes(str,str[start],start);
// 	if(end == -1)
// 	{
// 		return;
// 	}
// 	new = new_string(str,start,end);
// 	len = strlen(new);
// 	str =malloc(len+1);
// 	strcpy(str,new);
// }
// void remove_quotes_main_h(char *input)
// {
// 	int i = 0;
//     int a = 0;
// 	int end = 0;
// 	int single_quotes = 0;
// 	int double_quotes = 0;
// 	 int len = 0;
// 	 char *copy;
// 	// while(input[i])
// 	// {
// 		// if(strcmp((*head)->token,"<<") == 0)
// 		// {
// 		// 	if((*head) -> next -> next)
// 		// 		(*head) = (*head) -> next -> next;
// 		// 	else
// 		// 		break;
// 		// 	continue;
// 		// }
// 		i = 0;
// 		while(input[i])
// 		{
// 			if(input[i] == '"' && single_quotes == 0)
// 			{
// 				copy=ft_strdup(input);
// 				remove_quotes_and_replace_h(input,i);
// 			 	double_quotes++;
// 			len = strlen(input);
// 			end = find_end_of_quotes(copy,'"',i);
//             // break;
// 			// printf("end1 %d\n",end);

// 			if(end-1 > len)
// 			{
// 				break;
// 			}
// 			if(input[end-1])
// 			{
// 			i = end -1;
// 		    // printf("i :%d\n",i);
// 			single_quotes = 0;
// 	 		double_quotes = 0;
// 			}
// 			 continue;
// 			}
// 			if(input[i] == '\'' && double_quotes == 0)
// 			{
// 								copy=ft_strdup(input);
// 				remove_quotes_and_replace_h(input,i);
// 				single_quotes++;
// 							len = strlen(input);
// 					end = find_end_of_quotes(copy,'\'',i);
// 											// printf("end %d\n",end);
// 					if(end-1 >= len)
// 					{
// 						break;
// 					}
// 					if(input[end-1])
// 					{
// 					i = end -1;
// 						// printf("%d\n",i);
// 					single_quotes = 0;
// 					double_quotes = 0;
// 					}
// 										single_quotes = 0;
// 					double_quotes = 0;
// 					continue;
//                     i++;					
// 		 }
// 		// }
// 		// (*head) = (*head) -> next;
// 	}
// }
void expand_and_replace_heredoc(char **mainstr,char *str, int end)
{
    if(!str[0])
    {
            (*mainstr) = "";
            return;
    }
    char *s;
    int i = 0;
    int x = 0;
    s = strdup((*mainstr) + end);
    int len = strlen(str) + strlen(s);
    (*mainstr) = malloc(len + 1);
    while(str[i])
    {
        (*mainstr)[x] = str[i];
        i ++;
        x ++;
    }
    i = 0;
    while(s[i])
    {
        (*mainstr)[x] = s[i];
        i ++;
        x ++;
    }
    (*mainstr)[x] = '\0';

}
char *create_array_till_dollar_h(char *input,int index)
{
    char * new_string;
    int i;
    i = 0;
    new_string = NULL;
    new_string = malloc(index+1);
    while(i < index)
    {
        new_string[i] = input[i];
        i++;
    }
    new_string[i] = '\0';
    return(new_string);
}
char *check_char_after_dollar1(char *str,t_env *envp,t_shell *exitcode)
{
    char *new_string = NULL;
    if((str[0] == '$' && str[1] == '?'))
    {
     new_string = ft_itoa(exitcode -> exit_code);
    }
     else if(str[0] == '$' && (str[1] == '"' || str[1] == '\'') )
    {
        new_string = strdup(str+1);
    }
    else if(str[0] == '$' && (str[1] >= '0' && str[1] <= '9'))
    {
        new_string = strdup(str+2);
    }
    else if((is_num_or_char(str[1]) == 0 && (str[1] != '_')))
    {
        new_string = strdup(str);
    }
    else if((is_num_or_char(str[1]) == 1 || (str[1] == '_')))
     {//check ffirst charr
        new_string = expand_dollar(str,envp);
     }
    //  printf("null1");
    return (new_string);
}
int check_if_quotes_exit(char *input)
{
    int count;
    int i;
    i = 0;
    count = 0;
    while(input[i])
    {
        if(input[i] == '"' || input[i] == '\'')
            count ++;
        i ++;
    }
    return (count);
}
void  main_dollar_helper_h(int *i,char **input,char **str,t_env *env,t_shell *exitcode)
{
    int start = 0;
    char *expanded;
    int end;
    char *to_expand;
            if((*input)[(*i)] == '$')
            {
               (*str) = create_array_till_dollar_h((*input),(*i));
               start = (*i);
               end = find_end_variable((*input),(*i));
               to_expand = strndup((*input)+start,end -start);
                expanded = check_char_after_dollar1(to_expand,env,exitcode);
                if(expanded == NULL)
                {
                    expand_and_replace_heredoc(input,(*str),end);
                    (*i) = strlen((*str)) -1;
                }
                else if(expanded)
                {
                    char *temp = ft_strjoin((*str),expanded);
                    free((*str));
                    (*str) = temp;
                    free(to_expand);
                    free(expanded);
                     expand_and_replace_heredoc(input,(*str),end);
                    (*i) = strlen((*str))-1 ;
                    
                }
                else
                {
                    (*i)= end;
                }

            }
}
void main_dollar_heredoc(char **input, t_env *env,t_shell *exitcode)
{
    int i = 0;
    char *str = NULL;
    int end = 0;
    char *to_expand = NULL;
    int start = 0;
    char *expanded;
    int len = 0;
        while(input[i])
        {
            main_dollar_helper_h(&i, input, &str, env,exitcode);
            i++;
        }
    
  
 }
int find_end_of_quotes_h(char *str, char quote,int start)
{
	int x= start+1 ;
	// printf("\n%s\n",str);
	while(str[x])
	{
		if(str[x] == quote)
			return(x);
		x++;
	}
	return(-1);
}
void remove_quotes_and_replace_h(char **str,int start)
{
	int end = 0;
	char *new = NULL;
	int len =0;
	end = find_end_of_quotes_h((*str),(*str)[start],start);
	if(end == -1)
	{
		return;
	}
	new = new_string((*str),start,end);
	len = strlen(new);
	(*str) =malloc(len+1);
	strcpy((*str),new);
}  


void remove_quotes_main_heredoc(char **str)
{
    int i = 0, end = 0, single_quotes = 0, double_quotes = 0;
    int len = 0;
    char *copy;

    while ((*str)[i])
    {
        if ((*str)[i] == '"' && single_quotes == 0)
        {
            copy = ft_strdup((*str));  // Make a copy before modifying
            end = find_end_of_quotes_h(copy, '"', i);
            free(copy);

            if (end == -1 || end >= strlen(*str))
                break;

            remove_quotes_and_replace_h(str, i);
            i = end - 1;
            single_quotes = 0;
            double_quotes = 0;
            continue;
        }
        if ((*str)[i] == '\'' && double_quotes == 0)
        {
            copy = ft_strdup((*str));
            end = find_end_of_quotes_h(copy, '\'', i);
            free(copy);

            if (end == -1 || end >= strlen(*str))
                break;

            remove_quotes_and_replace_h(str, i);
            i = end - 1;
            single_quotes = 0;
            double_quotes = 0;
            continue;
        }
        i++;
    }
}
