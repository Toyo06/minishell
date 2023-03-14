/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:38:15 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/14 18:24:29 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(t_list **lst, t_env **env)
{
    t_list	*tmp;
    char    cwd[2048];

	tmp = (*lst);
	g_base.cd.arg_count = 0;
    while (tmp)
	{
        g_base.cd.arg_count++;
        tmp = tmp->next;
    }
    if (g_base.cd.arg_count > 2)
        return (err_msg_cd(6));
    tmp = (*lst)->next;
    if (tmp == NULL)
        g_base.cd.path = ft_getenv(env, "HOME");
	else
        g_base.cd.path = tmp->arg;
    if (g_base.cd.path == NULL)
        return (err_msg_cd(7));
    if (chdir(g_base.cd.path) == -1)
        return (err_msg_cd(8));
    if (!ft_getenv(env, "PWD"))
        ft_update_env(env, "PWD", getcwd(cwd, sizeof(cwd)));
    ft_update_env(env, "OLDPWD", ft_getenv(env, "PWD"));
    ft_update_env(env, "PWD", getcwd(cwd, sizeof(cwd)));
    register_pwd();
}
