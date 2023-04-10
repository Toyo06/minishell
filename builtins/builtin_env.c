/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:37:04 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 02:45:49 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env **env, t_list **lst, int fd)
{
	(void)lst;
	ft_printenv(env, fd);
	exit_condition(0);
	return ;
}

void	ft_printenv(t_env **env, int fd)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (tmp->name != NULL && tmp->content != NULL)
		{
			ft_putstr_fd(tmp->name, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(tmp->content, fd);
			ft_putstr_fd("\n", fd);
		}
		tmp = tmp->next;
	}
}
