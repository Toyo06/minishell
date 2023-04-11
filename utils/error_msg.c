/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:40:03 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/01 13:21:10 by sroggens         ###   ########.fr       */
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
	else if (i == 2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
			2);
		g_base.retval.code = 258;
	}
}

void	err_msg_exit(int i)
{
	if (i == 3)
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
	else if (i == 4)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n",
			2);
		g_base.retval.code = 1;
	}
}

void	err_msg_export(int i)
{
	if (i == 5)
	{
		ft_putstr_fd("minishell: export: not a valid identifier\n",
			2);
		g_base.retval.code = 1;
	}
}

void	err_msg_cd(int i)
{
	if (i == 6)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_base.retval.code = 1;
	}
	else if (i == 7)
	{
		ft_putstr_fd("cd: no home directory\n", 2);
		g_base.retval.code = 1;
	}
	else if (i == 8)
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		g_base.retval.code = 1;
	}
}

void	err_msg_unset(int i)
{
	if (i == 9)
	{
		ft_putstr_fd("minishell: unset: not a valid identifier\n",
			2);
		g_base.retval.code = 1;
	}
}
