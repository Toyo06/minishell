/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:45:43 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 11:53:40 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo_output(t_list **tmp, int fd)
{
	while (*tmp && (*tmp)->data != 6)
	{
		if ((*tmp)->data == 8)
			ft_putstr_fd(ft_itoa(g_base.retval.code), fd);
		else if ((*tmp)->data == 10)
			ft_putstr_fd((*tmp)->arg, fd);
		if ((*tmp)->next == NULL)
			break ;
		if ((*tmp)->next != NULL && (*tmp)->next->data == 10)
			ft_putstr_fd(" ", fd);
		*tmp = (*tmp)->next;
	}
}

void	prepare_echo(t_list **lst, t_list **tmp, int fd)
{
	(*tmp) = (*lst)->next;
	if ((*tmp) == NULL || (*tmp)->data == 6)
	{
		ft_putstr_fd("\n", fd);
		return ;
	}
	while ((*tmp)->data != 10 && (*tmp)->data != 8)
	{
		if (!(*tmp))
			return ;
		(*tmp) = (*tmp)->next;
	}
}

void	ft_echo(t_list **lst, int fd)
{
	t_list	*tmp;

	prepare_echo(lst, &tmp, fd);
	if (tmp)
		g_base.echo.option = ft_checkoption(tmp->arg);
	if (g_base.echo.option == 1 && tmp->next == NULL)
	{
		exit_condition(0);
		return ;
	}
	handle_echo_option(&tmp);
	if (check_echo_option(tmp))
		tmp = tmp->next;
	print_echo_output(&tmp, fd);
	if (g_base.echo.option == 0)
		ft_putstr_fd("\n", fd);
	g_base.retval.code = 0;
	exit_condition(0);
	return ;
}
