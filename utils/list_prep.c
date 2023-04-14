/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:59:30 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/14 23:07:52 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	listchangeifquote(list);
	printthelist(list);
	return (check_sym_err(list));
}

void	listchangeifquote(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		tmp->arg = changeinsq(tmp->arg);
		tmp = tmp->next;
	}
}

char	*changeinsq(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '\'')
			i++;
		else
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}
