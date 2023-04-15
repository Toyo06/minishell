/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forbidden_char_checkbis.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:38:21 by sroggens          #+#    #+#             */
/*   Updated: 2023/04/15 13:02:11 by sroggens         ###   ########.fr       */
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

char	*addspacewhenneededpipe(char *str)
{
	setvalueforquotepipe();
	g_base.spaceoppipe.rtv = malloc(sizeof(char)
			* (countmallocnewstring(str)) + 1);
	while (str[g_base.spaceoppipe.i])
	{
		if (str[g_base.spaceoppipe.i] == '"')
			doublequotechecker(str);
		else if (str[g_base.spaceoppipe.i] == '\'')
			singlequotechecker(str);
		else if (str[g_base.spaceoppipe.i] == '\0')
			break ;
		else if (str[g_base.spaceoppipe.i] == '|'
			|| (g_base.spaceoppipe.i > 0
				&& str[g_base.spaceoppipe.i - 1] == '|'))
			addspacewhenneededbro();
		g_base.spaceoppipe.rtv[g_base.spaceoppipe.j]
			= str[g_base.spaceoppipe.i];
		g_base.spaceoppipe.i++;
		g_base.spaceoppipe.j++;
	}
	g_base.spaceoppipe.rtv[g_base.spaceoppipe.j] = '\0';
	return (returnwhatiwant(str));
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

void	addspacewhenneededbro(void)
{
	g_base.spaceoppipe.rtv[g_base.spaceoppipe.j] = ' ';
	g_base.spaceoppipe.j++;
}
