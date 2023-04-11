/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 02:44:44 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 20:23:54 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_echo_option(t_list *tmp)
{
	if (tmp && tmp->next != NULL && ft_checkoption(tmp->arg)
		&& tmp->next != NULL)
		return (1);
	return (0);
}

void	handle_echo_option(t_list **tmp)
{
	while ((*tmp) && (*tmp)->next != NULL && g_base.echo.option == 1)
	{
		(*tmp) = (*tmp)->next;
		if (ft_checkoption((*tmp)->arg) && (*tmp)->next == NULL)
		{
			exit_condition(0);
			return ;
		}
		else if (!ft_checkoption((*tmp)->arg))
			break ;
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
