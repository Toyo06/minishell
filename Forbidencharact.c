/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seelater.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:10:49 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/19 00:19:14 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	checkforbiden(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ';')
		{
			ft_printf("\';\' not allowed on our minishell.\n");
			return (0);
		}
		if (str[i] == '\\')
		{
			ft_printf("'\\' not allowed on our minishell.\n");
			return (0);
		}
		i++;
	}
	return (1);
}
