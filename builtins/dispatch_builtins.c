/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:31:06 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/11 16:51:04 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(char *arg)
{
	if (ft_strcmp("exit", arg) == 0)
		return (1);
	else if (ft_strcmp("export", arg) == 0)
		return (1);
	else if (ft_strcmp("unset", arg) == 0)
		return (1);
	else if (ft_strcmp("echo", arg) == 0 || ft_strcmp(ECHO_P, arg) == 0
		|| ft_strcmp("ECHO", arg) == 0)
		return (1);
	else if (ft_strcmp("pwd", arg) == 0 || ft_strcmp(PWD_P, arg) == 0
		|| ft_strcmp("PWD", arg) == 0)
		return (1);
	else if (ft_strcmp("env", arg) == 0 || ft_strcmp(ENV_P, arg) == 0
		|| ft_strcmp("ENV", arg) == 0)
		return (1);
	else if (ft_strcmp("cd", arg) == 0 || ft_strcmp(CD_P, arg) == 0
		|| ft_strcmp("CD", arg) == 0)
		return (1);
	return (0);
}

int	check_dispatch2(t_list **lst, t_env **env, int fd)
{
	if (ft_strcmp("exit", (*lst)->arg) == 0)
		ft_exit(lst, fd);
	else if (ft_strcmp("export", (*lst)->arg) == 0)
	{
		g_base.xport.disp2 = 1;
		ft_export_bis(lst, env, fd);
	}
	else if (ft_strcmp("unset", (*lst)->arg) == 0)
		check_unset(lst, env);
	else if (ft_strcmp("cd", (*lst)->arg) == 0
		|| ft_strcmp(CD_P, (*lst)->arg) == 0
		|| ft_strcmp("CD", (*lst)->arg) == 0)
		ft_cd(lst, env);
	else
		return (1);
	g_base.retval.pbuilt = 1;
	return (0);
}

void	dispatch2(t_list **lst, t_env **env, int fd)
{
	t_list	*tmp;

	tmp = (*lst);
	g_base.retval.pxit = 0;
	g_base.retval.pbuilt = 0;
	while (tmp && tmp->data != 6)
	{
		if (tmp->next && tmp->data != 10 && tmp->data != 8)
			tmp = tmp->next;
		if (check_dispatch2(&tmp, env, fd) == 0)
			return ;
		tmp = tmp->next;
	}
	return ;
}

void	isitabuiltin_bis(t_list **lst, t_env **env, int fd)
{
	if ((*lst)->next == NULL || ((*lst)->next != NULL
			&& ((*lst)->next->data == 6
				|| (*lst)->next->data == 4 || (*lst)->next->data == 3
				|| (*lst)->next->data == 11 || (*lst)->next->data == 2)))
		ft_printexport(env, 1);
	else
	{
		if (((*lst)->prev && (*lst)->data == 6) || g_base.xport.disp2 == 1)
			return ;
		ft_export(lst, env, fd);
	}
}

int	isitabuiltin(t_list	**lst, t_env **env, int fd)
{
	t_list	*tmp;

	tmp = (*lst);
	g_base.retval.pxit = 1;
	while (tmp && tmp->data != 6)
	{
		if (tmp->data != 10 && tmp->next != NULL)
			tmp = tmp->next;
		if (dispatch(&tmp, env, fd) == 0)
			return (0);
		if (tmp != NULL)
			tmp = tmp->next;
	}
	return (1);
}
