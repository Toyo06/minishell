/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:40:03 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/08 15:21:38 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	error_msg(int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
	}
	if (i == 2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
			2);
	}
	if (i == 3)
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n",
			2);
	}
	if (i == 4)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n",
			2);
		g_base.retval.code = 1;
	}
	if (i == 5)
	{
		ft_putstr_fd("minishell: export: not a valid identifier\n",
			2);
		g_base.retval.code = 1;
	}
}

