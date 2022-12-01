/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 07:56:04 by sroggens          #+#    #+#             */
/*   Updated: 2022/12/01 14:02:39 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	errormanagement(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	if ((tmp->data == 1 || tmp->data == 2 || tmp->data == 3 || tmp->data == 4)
		&& tmp->prev == NULL && tmp->next == NULL)
	{
		errormess(1);
		return (0);
	}
	if (tmp->data == 7 && tmp->prev == NULL && tmp->next == NULL)
	{
		errormess(2);
		return (0);
	}
	return (1);
}

int	check_heredoc(t_list **lst)
{
	t_list	*tmp;
	char	*str;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->data == 1)
		{
			while (1)
			{
				str = readline("> ");
				if (str && ft_strcmp(str, tmp->next->arg) == 0)
					break ;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
