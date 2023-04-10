/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:48:07 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 11:53:05 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_exit_zero_args(t_list *tmp, int fd)
{
	if (tmp->prev == NULL && tmp->next == NULL)
		g_base.retval.pxit = 0;
	display_exit(0, 0, fd);
}

void	handle_exit_multiple_args(t_list *tmp, int fd)
{
	while (tmp)
	{
		tmp = tmp->next;
		if (tmp->data == 6)
			display_exit(0, 0, fd);
		if (tmp->data != 10)
			continue ;
		if (!check_nb(tmp->arg))
			display_exit(255, 3, fd);
		else if (check_nb(tmp->arg) && tmp->next
			!= NULL && tmp->next->data != 6)
		{
			if (tmp->prev == NULL)
				g_base.retval.pxit = 0;
			display_exit(1, 4, fd);
			return ;
		}
		else
			display_exit(base_check(ft_atoi(tmp->arg)), 0, fd);
	}
}

void	handle_exit_cmd(t_list *tmp, int fd)
{
	int	exit_args;

	exit_args = check_exit_args(&tmp);
	if (exit_args == 0)
		handle_exit_zero_args(tmp, fd);
	else if (exit_args >= 1)
		handle_exit_multiple_args(tmp, fd);
}

void	ft_exit(t_list **lst, int fd)
{
	t_list	*tmp;

	tmp = (*lst);
	if (ft_strcmp(tmp->arg, "exit") == 0)
		handle_exit_cmd(tmp, fd);
}
