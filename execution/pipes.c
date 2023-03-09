/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:06:40 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/09 13:26:04 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(t_list **lst, t_env **env)
{
	if (checkpipes(lst) == 0)
		if (isitabuiltin(lst, env) == 1)
			execsimglecmd(lst, env);
	if (checkpipes(lst) == 1)
		if (isitabuiltin(lst, env) == 1)
			execonepipe(lst, env);
	if (checkpipes(lst) > 1)
		pipeline(env, lst);
}

int	isitabuiltin(t_list	**lst, t_env **env)
{
	if (ft_strcmp("echo", (*lst)->arg) == 0)
		ft_echo(lst, 0);
	else if (ft_strcmp("exit", (*lst)->arg) == 0)
		ft_exit(lst);
	else if (ft_strcmp("export", (*lst)->arg) == 0)
	{
		if ((*lst)->next == NULL)
			ft_printexport(env);
		else
			ft_export(lst, env);
	}
	else if (ft_strcmp("pwd", (*lst)->arg) == 0)
		ft_pwd(lst);
	else if (ft_strcmp("unset", (*lst)->arg) == 0)
		check_unset(lst, env);
	else if (ft_strcmp("cd", (*lst)->arg) == 0)
		ft_cd(lst, env);
	else if (ft_strcmp("env", (*lst)->arg) == 0)
		ft_env(env, lst);
	else
		return (1);
	return (0);
}
