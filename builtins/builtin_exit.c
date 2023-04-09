/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:48:07 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/09 22:32:20 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_exit_zero_args(t_list *tmp)
{
	if (tmp->prev == NULL && tmp->next == NULL)
		g_base.retval.pxit = 0;
	display_exit(0, 0);
}

void	handle_exit_multiple_args(t_list *tmp)
{
	g_base.retval.pxit = 1;
	if (tmp->next->data == 6)
		display_exit(0, 0);
	if (!check_nb(tmp->next->arg))
		display_exit(255, 3);
	else if (check_nb(tmp->next->arg) && tmp->next->next != NULL
		&& tmp->next->next->data != 6)
	{
		if (tmp->prev == NULL)
			g_base.retval.pxit = 0;
		display_exit(1, 4);
	}
	else
		display_exit(base_check(ft_atoi(tmp->next->arg)), 0);
}

void	handle_exit_cmd(t_list *tmp)
{
	int	exit_args;

	exit_args = check_exit_args(&tmp);
	if (exit_args == 0)
		handle_exit_zero_args(tmp);
	else if (exit_args >= 1)
		handle_exit_multiple_args(tmp);
}

void	ft_exit(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	g_base.retval.pxit = 1;
	if (ft_strcmp(tmp->arg, "exit") == 0)
	{
		handle_exit_cmd(tmp);
	}
}
