/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:06:40 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/28 21:11:03 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_empty(t_list **lst)
{
	t_list *tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->data == 10)
			return (0);
		else if (tmp->data == 6)
		{
			while ((*lst)->data == 6)
				(*lst) = (*lst)->next;
			(*lst) = (*lst)->next;
			(*lst) = (*lst)->next;
			tmp = (*lst);
			printf(YEL "%d" CRESET "\n", tmp->data);
		}
		if (tmp->next == NULL)
			return (1);
		tmp = tmp->next;
	}
	return (1);
}

int		check_builtin(char *arg)
{
	if (ft_strcmp("exit", arg) == 0)
		return (1);
	else if (ft_strcmp("export", arg) == 0)
		return (1);
	else if (ft_strcmp("unset", arg) == 0)
		return (1);
	else if (ft_strcmp("echo", arg) == 0 || ft_strcmp(ECHO_P, arg) == 0)
		return (1);
	else if (ft_strcmp("pwd", arg) == 0 || ft_strcmp(PWD_P, arg) == 0)
		return (1);
	else if (ft_strcmp("env", arg) == 0 || ft_strcmp(ENV_P, arg) == 0)
		return (1);
	else if (ft_strcmp("cd", arg) == 0 || ft_strcmp(CD_P, arg) == 0)
		return (1);
	return (0);
}

void	execution(t_list **lst, t_env **env)
{
	int	retval;

	retval = 0;
	g_base.retval.pcd = 0;
	g_base.retval.inp = 0;
	redirection(lst);
	countheredoc(lst);
	while (1)
	{
		retval = heredoc(lst);
		if (retval == 1)
			break ;
		if (retval == 2)
			return ;
	}
	if (checkpipes(lst) == 0)
		if (isitabuiltin(lst, env) == 1)
			execsimglecmd(lst, env);
	if (checkpipes(lst) == 1)
			execonepipe(lst, env);
	if (checkpipes(lst) > 1)
		pipeline(env, lst);
}

int	isitabuiltin(t_list	**lst, t_env **env)
{
	if (ft_strcmp("echo", (*lst)->arg) == 0
		|| ft_strcmp(ECHO_P, (*lst)->arg) == 0)
		ft_echo(lst, 1);
	else if (ft_strcmp("exit", (*lst)->arg) == 0)
		ft_exit(lst);
	else if (ft_strcmp("export", (*lst)->arg) == 0)
	{
		if ((*lst)->next == NULL || (*lst)->next->data == 6)
			ft_printexport(env);
		else
			ft_export(lst, env);
	}
	else if (ft_strcmp("pwd", (*lst)->arg) == 0
			|| ft_strcmp(PWD_P, (*lst)->arg) == 0)
		ft_pwd(lst);
	else if (ft_strcmp("unset", (*lst)->arg) == 0)
		check_unset(lst, env);
	else if (ft_strcmp("cd", (*lst)->arg) == 0
			|| ft_strcmp(CD_P, (*lst)->arg) == 0)
		ft_cd(lst, env);
	else if (ft_strcmp("env", (*lst)->arg) == 0
			|| ft_strcmp(ENV_P, (*lst)->arg) == 0)
		ft_env(env, lst);
	else
		return (1);
	return (0);
}
