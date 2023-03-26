/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:38:15 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/27 01:30:28 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(t_list **lst, t_env **env)
{
	t_list	*tmp;
	char	cwd[2048];

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->next && tmp->next->data == 6)
			break ;
		tmp = tmp->next;
	}
	tmp = (*lst)->next;
	if (tmp == NULL || tmp->data == 6)
		g_base.cd.path = ft_getenv(env, "HOME");
	else
		g_base.cd.path = tmp->arg;
	if (g_base.cd.path == NULL)
	{
		err_msg_cd(7);
		if (g_base.retval.pcd == 1)
			exit (1);
		return ;
	}
	if (chdir(g_base.cd.path) == -1)
	{
		err_msg_cd(8);
		if (g_base.retval.pcd == 1)
			exit (1);
		return ;
	}
	if (!ft_getenv(env, "PWD"))
		ft_update_env(env, "PWD", getcwd(cwd, sizeof(cwd)));
	ft_update_env(env, "OLDPWD", ft_getenv(env, "PWD"));
	ft_update_env(env, "PWD", getcwd(cwd, sizeof(cwd)));
	register_pwd();
}
