/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_utils_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:14:06 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 22:14:33 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_b_cd(t_list **lst, t_env **env)
{
	if (ft_strcmp("cd", (*lst)->arg) == 0
		|| ft_strcmp(CD_P, (*lst)->arg) == 0
		|| ft_strcmp("CD", (*lst)->arg) == 0)
	{
		if (g_base.retval.pbuilt == 1)
			exit(0);
		ft_cd(lst, env);
		return (1);
	}
	return (0);
}

int	check_b_env(t_list **lst, t_env **env, int fd)
{
	if (ft_strcmp("env", (*lst)->arg) == 0
		|| ft_strcmp(ENV_P, (*lst)->arg) == 0
		|| ft_strcmp("ENV", (*lst)->arg) == 0)
	{
		ft_env(env, lst, fd);
		return (1);
	}
	return (0);
}

int	dispatch(t_list **lst, t_env **env, int fd)
{
	fd = 1;
	if (check_b_echo(lst, fd))
		return (0);
	else if (check_b_exit(lst, fd))
		return (0);
	else if (check_b_export(lst, env, fd))
		return (0);
	else if (check_b_pwd(lst, fd))
		return (0);
	else if (check_b_unset(lst, env))
		return (0);
	else if (check_b_cd(lst, env))
		return (0);
	else if (check_b_env(lst, env, fd))
		return (0);
	else
		return (1);
}
