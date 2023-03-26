/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:48:07 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/26 23:31:34 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	g_base.retval.pxit = 1;
	if (ft_strcmp(tmp->arg, "exit") == 0)
	{
		if (check_exit_args(lst) == 0)
		{
			if (tmp->prev == NULL && tmp->next == NULL)
				g_base.retval.pxit = 0;
			display_exit(0, 0);
		}
		else if (check_exit_args(lst) >= 1)
		{
			g_base.retval.pxit = 1;
			if (tmp->next->data == 6)
				display_exit(0, 0);
			if (!check_nb(tmp->next->arg))
				display_exit(255, 3);
			else if (check_nb(tmp->next->arg) && tmp->next->next != NULL && tmp->next->next->data != 6)
			{
				if (tmp->prev == NULL)
					g_base.retval.pxit = 0;
				display_exit(1, 4);
			}
			else
				display_exit(base_check(ft_atoi(tmp->next->arg)), 0);
		}
	}
}

int	base_check(int nb)
{
	while (nb > 256)
		nb -= 256;
	return (nb);
}

int	check_nb(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	display_exit(int nb, int choice)
{
	if (g_base.retval.pxit != 1)
		printf("exit\n");
	if (choice == 1)
		error_msg(1);
	else if (choice == 3)
		err_msg_exit(3);
	else if (choice == 4)
	{
		err_msg_exit(4);
		if (g_base.retval.pxit == 1)
			exit (1);
		else if (g_base.retval.pxit == 0)
			return ;
	}
	exit (nb);
}

int	check_exit_args(t_list **lst)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = (*lst);
	while (tmp->next)
	{
		if (tmp->data == 6)
			break ;
		tmp = tmp->next;
		i++;
	}
	return (i);
}
