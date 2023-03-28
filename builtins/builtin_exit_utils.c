/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:40:47 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/28 20:44:52 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_condition(int n)
{
	if (g_base.retval.inp == 1)
		exit(n);
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
