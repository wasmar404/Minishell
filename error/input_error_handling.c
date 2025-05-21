/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:14:57 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/21 13:23:22 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

/* check if the first node is a command
 if there is a pipe, check if the node before and the node after is a command
 if there is input redirection, check if the file exists and has permissions
 check if quotes are balanced, if a single q exists in a double q,
	consider it a character
 if there is an output redirection, check if file name exists,
	and if it exists check permissions
 cat << : check that parameter exists after <<
 check if command is valid

 */
// long long exit_code;
int	check_command_helper(char *array, t_shell *exitcode)
{
	if (array[0] == '.' && array[1] == '/' && access(array, X_OK) == 0)
	{
		exitcode->exit_code = 0;
		return (1);
	}
	else if (array[0] == '.' && array[1] == '/' && access(array, X_OK) != 0)
	{
		exitcode->exit_code = 127;
		ft_putendl_fd("bash: ./test: No such file or directory", 2);
		return (0);
	}
}
