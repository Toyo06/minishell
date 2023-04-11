/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forbidden_char_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:29:55 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 13:46:51 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	countmallocnewstring(char *str)
{
	int		i;
	int		count;
	char	tmp;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|')
			count += 2;
		else if (str[i] == '"' || str[i] == '\'')
		{
			tmp = (str[i]);
			count++;
			i++;
			while (str[i] != tmp)
			{
				count++;
				i++;
			}
		}
		count++;
		i++;
	}
	return (count);
}

void	singlequotechecker(char *str)
{
	g_base.spaceoppipe.rtv[g_base.spaceoppipe.j]
		= str[g_base.spaceoppipe.i];
	g_base.spaceoppipe.j++;
	g_base.spaceoppipe.i++;
	while (str[g_base.spaceoppipe.i]
		&& str[g_base.spaceoppipe.i] != '\'')
	{
		g_base.spaceoppipe.rtv[g_base.spaceoppipe.j]
			= str[g_base.spaceoppipe.i];
		g_base.spaceoppipe.i++;
		g_base.spaceoppipe.j++;
	}
}

void	doublequotechecker(char *str)
{
	g_base.spaceoppipe.rtv[g_base.spaceoppipe.j] = str[g_base.spaceoppipe.i];
	g_base.spaceoppipe.j++;
	g_base.spaceoppipe.i++;
	while (str[g_base.spaceoppipe.i]
		&& str[g_base.spaceoppipe.i] != '"')
	{
		g_base.spaceoppipe.rtv[g_base.spaceoppipe.j]
			= str[g_base.spaceoppipe.i];
		g_base.spaceoppipe.i++;
		g_base.spaceoppipe.j++;
	}
}
