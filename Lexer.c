/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 23:58:02 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/24 11:50:24 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_base	g_base;

char	*removequote(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (str[0] != 34 && str[0] != 39)
		return (str);
	g_base.quote.nextquote = str[0];
	new_str = malloc(sizeof(char) * ft_strlen(str) - 1);
	while (str[i])
	{
		if (str[i] != g_base.quote.nextquote)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

int	checkthestart(char *str, t_list **lst)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!(checkforbiden(str)) || !(checkquote(str)))
		return (0);
	else
	{
		changebetweenquote(str);
		new_str = addspace_be_foreop(str);
		g_base.parsing.tab = ft_split(new_str, ' ');
		g_base.parsing.tab = rechangebetweenquote(g_base.parsing.tab);
		while (g_base.parsing.tab[i])
		{
			g_base.parsing.tab[i] = removequote(g_base.parsing.tab[i]);
			i++;
		}
		prepalist(lst, g_base.parsing.tab);
		free(g_base.parsing.tab);
		free(new_str);
	}
	return (1);
}
