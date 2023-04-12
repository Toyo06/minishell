/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:59:30 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/12 21:41:20 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_lst_data(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (double_char(str) != 0)
			return (double_char(str));
		if (single_char(str) != 0)
			return (single_char(str));
		else if (str[i + 1] == '\0')
			return (10);
		i++;
	}
	return (0);
}

int	double_char(char *str)
{
	if ((str[0] == '>' && str[1] == '>') || (str[0] == '<' && str[0] == '<' )
		|| (str[0] == '$' && str[1] == '?' && str[2] == '\0'))
	{
		if (str[0] == '>' && str[1] == '>' && str[2] == '\0')
			return (3);
		if (str [0] == '<' && str[1] == '<' && str[2] == '\0')
			return (1);
		if (str[0] == '$' && str[1] == '?' && str[2] == '\0')
			return (8);
	}
	return (0);
}

int	single_char(char *str)
{
	if ((str[0] == '>' || str[0] == '<' || str[0] == '|')
		&& double_char(str) == 0)
	{
		if (str[0] == '>' && str[1] == '\0')
			return (4);
		if (str[0] == '<' && str[1] == '\0')
			return (2);
		if (str[0] == '|' && str[1] == '\0')
			return (6);
	}
	return (0);
}

int	list_prep(t_list **list, char **arr)
{
	int		i;
	int		j;
	t_list	*tmp;

	i = 0;
	while (arr[i])
	{
		j = set_lst_data(arr[i]);
		if ((*list) == NULL)
			add_node(list, j, arr[i]);
		else
		{
			add_node(&tmp, j, arr[i]);
			add_next_node(list, tmp);
		}
		i++;
	}
	return (check_sym_err(list));
}
