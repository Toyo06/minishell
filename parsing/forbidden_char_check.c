/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forbidden_char_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:29:55 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 12:23:20 by sroggens         ###   ########.fr       */
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

size_t	countmallocnewstring(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|')
			count += 2;
		else if (str[i] == '"')
		{
			count++;
			i++;
			while (str[i] != '"')
			{
				count++;
				i++;
			}
		}
		else if (str[i] == '\'')
		{
			count++;
			i++;
			while (str[i] != '\'')
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

char	*addspacewhenneededpipe(char *str)
{
	char	*rtv;

	setvalueforquotepipe();
	rtv = malloc(sizeof(char) * (countmallocnewstring(str)) + 1);
	while (str[g_base.spaceoppipe.i])
	{
		if (str[g_base.spaceoppipe.i] == '"')
		{
			rtv[g_base.spaceoppipe.j] = str[g_base.spaceoppipe.i];
			g_base.spaceoppipe.j++;
			g_base.spaceoppipe.i++;
			while (str[g_base.spaceoppipe.i]
				&& str[g_base.spaceoppipe.i] != '"')
			{
				rtv[g_base.spaceoppipe.j] = str[g_base.spaceoppipe.i];
				g_base.spaceoppipe.i++;
				g_base.spaceoppipe.j++;
			}
		}
		else if (str[g_base.spaceoppipe.i] == '\'')
		{
			rtv[g_base.spaceoppipe.j] = str[g_base.spaceoppipe.i];
			g_base.spaceoppipe.j++;
			g_base.spaceoppipe.i++;
			while (str[g_base.spaceoppipe.i]
				&& str[g_base.spaceoppipe.i] != '\'')
			{
				rtv[g_base.spaceoppipe.j] = str[g_base.spaceoppipe.i];
				g_base.spaceoppipe.i++;
				g_base.spaceoppipe.j++;
			}
		}
		else if (str[g_base.spaceoppipe.i] == '\0')
			break ;
		else if (str[g_base.spaceoppipe.i] == '|' || (g_base.spaceoppipe.i > 0
				&& str[g_base.spaceoppipe.i - 1] == '|'))
		{
			rtv[g_base.spaceoppipe.j] = ' ';
			g_base.spaceoppipe.j++;
		}
		rtv[g_base.spaceoppipe.j] = str[g_base.spaceoppipe.i];
		g_base.spaceoppipe.i++;
		g_base.spaceoppipe.j++;
	}
	rtv[g_base.spaceoppipe.j] = '\0';
	return (rtv);
}

void	setvalueforquotepipe(void)
{
	g_base.spaceoppipe.i = 0;
	g_base.spaceoppipe.j = 0;
}

void	checkstatusquotepipe(char *str)
{
	if (str[g_base.spaceoppipe.i] == '"' && g_base.spaceoppipe.quote == 0)
		g_base.spaceoppipe.quote = 1;
	if (str[g_base.spaceoppipe.i] == '"' && g_base.spaceoppipe.quote == 1)
		g_base.spaceoppipe.quote = 0;
}
