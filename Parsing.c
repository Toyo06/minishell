/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 07:56:04 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/28 11:36:21 by sroggens         ###   ########.fr       */
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
