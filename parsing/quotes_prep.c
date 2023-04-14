/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_prep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:39:07 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/14 23:17:51 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*addcoping(char *str, char *new_str)
{
	if (str[g_base.rmquote.i] == '\'')
	{
		new_str[g_base.rmquote.j] = str[g_base.rmquote.i];
		g_base.rmquote.i++;
		g_base.rmquote.j++;
		while (str[g_base.rmquote.i] != '\'')
		{
			new_str[g_base.rmquote.j] = str[g_base.rmquote.i];
			g_base.rmquote.i++;
			g_base.rmquote.j++;
		}
		new_str[g_base.rmquote.j] = str[g_base.rmquote.i];
		g_base.rmquote.i++;
		g_base.rmquote.j++;
	}
	return (new_str);
}

char	*addcoping2(char *str, char *new_str)
{
	if (str[g_base.rmquote.i] == '"')
	{
		g_base.rmquote.i++;
		while (str[g_base.rmquote.i] != '"')
		{
			new_str[g_base.rmquote.j] = str[g_base.rmquote.i];
			g_base.rmquote.i++;
			g_base.rmquote.j++;
		}
		g_base.rmquote.i++;
	}
	return (new_str);
}

char	*addcoping3(char *str, char *new_str)
{
	new_str[g_base.rmquote.j] = str[g_base.rmquote.i];
	g_base.rmquote.i++;
	g_base.rmquote.j++;
	return (new_str);
}

void	sortrm(char *str)
{
	g_base.quote.nextquote = str[g_base.rmquote.i];
	if (str[g_base.rmquote.i] != '\0')
		g_base.rmquote.i++;
}
