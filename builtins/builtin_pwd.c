/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:27:47 by mayyildi          #+#    #+#             */
/*   Updated: 2023/02/17 00:25:30 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	register_pwd(void)
{
	g_base.pwd.pwd = getcwd(g_base.pwd.buf, sizeof(g_base.pwd.buf));
	// t_env	*tmp;

	// tmp = (*env);
	// while (tmp)
	// {
	// 	if (ft_strncmp(tmp->name, "PWD", 3) == 0)
	// 	{
	// 		g_base.pwd.pwd = ft_strdup(tmp->content);
	// 		printf("%s\n", g_base.pwd.pwd);
	// 		return ;
	// 	}
	// 	tmp = tmp->next;
	// }
}

void	ft_pwd(t_list **lst)
{
	(void)lst;
	if (g_base.pwd.pwd)
		printf("%s\n", g_base.pwd.pwd);
	else
		printf("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
}
