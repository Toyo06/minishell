/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:11:25 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/11 20:36:59 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_b_echo(t_list **lst, int fd)
{
	if (ft_strcmp("echo", (*lst)->arg) == 0
		|| ft_strcmp(ECHO_P, (*lst)->arg) == 0
		|| ft_strcmp("ECHO", (*lst)->arg) == 0)
	{
		ft_echo(lst, fd);
		return (1);
	}
	return (0);
}

int	check_b_exit(t_list **lst, int fd)
{
	if (ft_strcmp("exit", (*lst)->arg) == 0)
	{
		if (g_base.retval.pbuilt == 1)
			exit(g_base.retval.code);
		ft_exit(lst, fd);
		return (1);
	}
	return (0);
}

int	check_b_export(t_list **lst, t_env **env, int fd)
{
	if (ft_strcmp("export", (*lst)->arg) == 0)
	{
		isitabuiltin_bis(lst, env, fd);
		return (1);
	}
	return (0);
}

int	check_b_pwd(t_list **lst, int fd)
{
	if (ft_strcmp("pwd", (*lst)->arg) == 0
		|| ft_strcmp(PWD_P, (*lst)->arg) == 0
		|| ft_strcmp("PWD", (*lst)->arg) == 0)
	{
		ft_pwd(lst, fd);
		return (1);
	}
	return (0);
}

int	check_b_unset(t_list **lst, t_env **env)
{
	if (ft_strcmp("unset", (*lst)->arg) == 0)
	{
		if (g_base.retval.pbuilt == 1)
			exit(g_base.retval.code);
		check_unset(lst, env);
		return (1);
	}
	return (0);
}
