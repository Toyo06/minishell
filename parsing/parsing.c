/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:46:50 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/11 22:29:32 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	err_management(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	if ((tmp->data == 1 || tmp->data == 2 || tmp->data == 3 || tmp->data == 4)
		&& tmp->prev == NULL && tmp->next == NULL)
	{
		g_base.retval.code = 258;
		error_msg(1);
		return (0);
	}
	if (tmp->data == 6 && tmp->prev == NULL && tmp->next == NULL)
	{
		g_base.retval.code = 258;
		error_msg(2);
		return (0);
	}
	return (1);
}

int	check_sym_err(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->data == 8)
		{
			tmp->arg = ft_strdup(ft_itoa(g_base.retval.code));
			if (tmp->prev == NULL || tmp->prev->data == 6)
				return (checkeight(&tmp));
		}
		tmp = tmp->next;
		g_base.err.count++;
	}
	return (0);
}

int	checktwofour(void)
{
	g_base.retval.code = 258;
	error_msg(1);
	return (1);
}

int	checkthree(void)
{
	g_base.retval.code = 258;
	error_msg(1);
	return (1);
}

int	checksix(void)
{
	g_base.retval.code = 258;
	error_msg(1);
	return (1);
}
