/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quote_preparator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 23:55:29 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/23 11:53:12 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_base	g_base;

char	*changebetweenquote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			g_base.quote.nextquote = str[i];
			i++;
			while (str[i])
			{
				if (str[i] == g_base.quote.nextquote)
					break ;
				if (str[i] == ' ')
					str[i] = '\n';
				i++;
			}
		}
		i++;
	}
	return (str);
}

char	*replacebetweenquote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = ' ';
		i++;
	}
	return (str);
}

char	**rechangebetweenquote(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '\"' || tab[i][0] == '\'')
			tab[i] = replacebetweenquote(tab[i]);
		i++;
	}
	return (tab);
}
