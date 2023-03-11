/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:46:50 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/09 19:58:04 by mayyildi         ###   ########.fr       */
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
	int	count;

	tmp = (*lst);
	count = 0;
	while (tmp)
	{
		if (tmp->data == 6 && (tmp->next == NULL ||
				tmp->prev == NULL || tmp->next->data != 10 ||
				tmp->prev->data != 10))
		{
			g_base.retval.code = 258;
			error_msg(1);
			return (1);
		}
		if (tmp->data == 3 && (tmp->next == NULL ||
				tmp->next->data != 10))
		{
			g_base.retval.code = 258;
			error_msg(1);
			return (1);
		}
		if ((tmp->data == 2 || tmp->data == 4) &&
				(tmp->next == NULL || tmp->next->data != 10))
		{
			g_base.retval.code = 258;
			error_msg(1);
			return (1);
		}
		// if (tmp->data == 8)
		// {

		// 	if (tmp->prev == NULL ||
		// 			ft_strcmp(tmp->prev->arg, "echo") != 0 ||
		// 			count > 1)
		// 	{
		// 		error_msg(1);
		// 		return (1);
		// 	}
		// }
		tmp = tmp->next;
		count++;
	}
	return (0);
}
