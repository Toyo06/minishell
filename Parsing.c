/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 23:58:02 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/19 00:56:12 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_base	g_base;

int	checkthestart(char *str, t_list **lst)
{
	if (!(checkforbiden(str)) || !(checkquote(str)))
		return (0);
	else
	{
		changebetweenquote(str);
		g_base.parsing.tab = ft_split(str, ' ');
		g_base.parsing.tab = rechangebetweenquote(g_base.parsing.tab);
		prepalist(lst, g_base.parsing.tab);
		free(g_base.parsing.tab);
	}
	return (1);
}
