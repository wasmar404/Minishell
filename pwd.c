/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:13:08 by schaaban          #+#    #+#             */
/*   Updated: 2025/01/23 11:34:54 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int main_pwd()
{
    char cwd[10000];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        return (1);
        printf("error");
    }
    return (0);

}

