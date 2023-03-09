/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:31:06 by mayyildi          #+#    #+#             */
/*   Updated: 2023/02/16 22:41:22 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dispatch_builtins(t_list **lst, t_env **env)
{
	if (ft_strcmp((*lst)->arg, "echo") == 0)
		ft_echo(lst, 0);
	else if (ft_strcmp((*lst)->arg, "export") == 0)
	{
		if ((*lst)->next == NULL)
			ft_printexport(env);
		else
			ft_export(lst, env);
	}
	else if (ft_strcmp((*lst)->arg, "env") == 0)
		ft_printenv(env);
	else if (ft_strcmp((*lst)->arg, "exit") == 0)
		ft_exit(lst);
	else if (ft_strcmp((*lst)->arg, "pwd") == 0)
		ft_pwd(lst);
	else if (ft_strcmp((*lst)->arg, "unset") == 0)
		check_unset(lst, env);
	else if (ft_strcmp((*lst)->arg, "cd") == 0)
		ft_cd(lst, env);
}
