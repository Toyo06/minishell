/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:45:43 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/28 20:43:25 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_echo_option(t_list *tmp)
{
	if (tmp->next != NULL && ft_checkoption(tmp->arg)
		&& tmp->next != NULL)
		return 1;
	return 0;
}

void handle_echo_option(t_list **tmp)
{
	while ((*tmp)->next != NULL && g_base.echo.option == 1)
	{
		*tmp = (*tmp)->next;
		if (ft_checkoption((*tmp)->arg) && (*tmp)->next == NULL)
		{
			exit_condition(0);
			return;
		}
		else if (!ft_checkoption((*tmp)->arg))
			break;
	}
}

void print_echo_output(t_list **tmp, int fd)
{
	while (*tmp || (*tmp)->next->data != 6)
	{
		if ((*tmp)->data == 8)
			ft_putstr_fd(ft_itoa(g_base.retval.code), fd);
		else
			ft_putstr_fd((*tmp)->arg, fd);
		if ((*tmp)->next == NULL)
			break;
		if ((*tmp)->next != NULL)
			ft_putstr_fd(" ", fd);
		*tmp = (*tmp)->next;
	}
}

int	ft_checkoption(char *str)
{
	int	i;

	i = 1;
	if (str == NULL)
		return (0);
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void ft_echo(t_list **lst, int fd)
{
	t_list *tmp;

	tmp = (*lst);
	tmp = tmp->next;
	if (tmp == NULL)
		return (ft_putstr_fd("\n", fd));
	g_base.echo.option = ft_checkoption(tmp->arg);
	if (g_base.echo.option == 1 && tmp->next == NULL)
	{
		exit_condition(0);
		return;
	}
	handle_echo_option(&tmp);
	if (check_echo_option(tmp))
		tmp = tmp->next;
	print_echo_output(&tmp, fd);
	if (g_base.echo.option == 0)
		ft_putstr_fd("\n", fd);
	g_base.retval.code = 0;
	exit_condition(0);
	return;
}
