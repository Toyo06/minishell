/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:45:43 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/17 21:52:24 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_list	**lst, int fd)
{
	t_list	*tmp;

	tmp = (*lst);
	tmp = tmp->next;
	if (tmp == NULL)
		return (ft_putstr_fd("\n", fd));
	g_base.echo.option = ft_checkoption(tmp->arg);
	if (g_base.echo.option == 1 && tmp->next == NULL)
		return ;
	while (tmp->next != NULL && g_base.echo.option == 1)
	{
		tmp = tmp->next;
		if (ft_checkoption(tmp->arg) && tmp->next == NULL)
			return ;
		else if (!ft_checkoption(tmp->arg))
			break ;
	}
	if (ft_checkoption(tmp->arg) && tmp->next != NULL)
		tmp = tmp->next;
	while (tmp || tmp->next->data != 6)
	{
		if (tmp->data == 8)
			ft_putstr_fd(ft_itoa(g_base.retval.code), fd);
		else
			ft_putstr_fd(tmp->arg, fd);
		if (tmp->next == NULL)
			break;
		if (tmp->next != NULL)
			ft_putstr_fd(" ", fd);
		tmp = tmp->next;
	}
	if (g_base.echo.option == 0)
		ft_putstr_fd("\n", fd);
	g_base.retval.code = 0;
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
