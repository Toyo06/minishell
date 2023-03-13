/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:45:43 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/13 16:44:34 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_list	**lst, int fd)
{
	t_list	*tmp;
	int		option;

	tmp = (*lst);
	tmp = tmp->next;
	if (tmp == NULL)
		return (ft_putstr_fd("\n", fd));
	option = ft_checkoption(tmp->arg);
	if (option == 1 && tmp->next == NULL)
		return ;
	if (tmp->next != NULL && option == 1)
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
	if (option == 0)
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
