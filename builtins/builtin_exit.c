/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:48:07 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/09 19:46:55 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	if (ft_strcmp(tmp->arg, "exit") == 0)
	{
		if (check_pipes(lst) == 0)
			display_exit(0, 0);
		else if (!check_nb(tmp->next->arg))
			display_exit(255, 3);
		else if (check_nb(tmp->next->arg) && tmp->next->next != NULL)
			display_exit(1, 4);
		else if (check_pipes(lst) > 1)
		{
			printf(RED "CHECK " CRESET "\n");
			error_msg(1);
			return ;
		}
		else
			display_exit(base_check(ft_atoi(tmp->next->arg)), 0);
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
	printf("exit\n");
	if (choice == 1)
		error_msg(1);
	else if (choice == 3)
		error_msg(3);
	else if (choice == 4)
	{
		error_msg(4);
		return ;
	}
	exit (nb);
}

int	check_pipes(t_list **lst)
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
