/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forbidden_char_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:29:55 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/25 19:18:38 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_forbidden_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ';')
		{
			printf("\';\' not allowed on our minishell.\n");
			return (1);
		}
		if (str[i] == '\\')
		{
			printf("'\\' not allowed on our minishell.\n");
			return (1);
		}
		i++;
	}
	return (0);
}
