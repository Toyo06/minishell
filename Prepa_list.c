/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prepa_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:38:16 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/26 14:53:19 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	selectforlist(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '<')
			return (1);
		else if (str[i] == '<')
			return (2);
		else if (str[i] == '>' && str[i + 1] != '>')
			return (3);
		else if (str[i] == '>')
			return (4);
		else if (str[i] == '|')
			return (7);
		else if (str[i] == '$' && str[i + 1] == '?')
			return (8);
		else if (str[i] == '$')
			return (9);
		else if (str[i + 1] == '\0')
			return (10);
		i++;
	}
	return (0);
}

void	prepalist(t_list **list, char **tab)
{
	int		i;
	t_list	*tmp;
	int		j;

	i = 0;
	while (tab[i])
	{
		j = selectforlist(tab[i]);
		if ((*list) == NULL)
			addnode(list, j, tab[i]);
		else
		{
			addnode(&tmp, j, tab[i]);
			addnextnode(list, tmp);
		}
		i++;
	}
}
