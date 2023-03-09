/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:38:15 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/07 18:58:25 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(t_list **lst, t_env **env)
{
    t_list	*tmp;
    char	*path;
    int		arg_count;
    char    cwd[2048];

	tmp = (*lst);
	arg_count = 0;
    while (tmp)
	{
        arg_count++;
        tmp = tmp->next;
    }
    if (arg_count > 2)
        return ((void)printf("cd: too many arguments\n"));
    tmp = (*lst)->next;
    if (tmp == NULL)
        path = ft_getenv(env, "HOME");
	else
        path = tmp->arg;
    if (path == NULL)
        return ((void)printf("cd: no home directory\n"));
    if (chdir(path) == -1)
        return ((void)printf("cd: %s: No such file or directory\n", path));
    if (!ft_getenv(env, "PWD"))
        ft_update_env(env, "PWD", getcwd(cwd, sizeof(cwd)));
    ft_update_env(env, "OLDPWD", ft_getenv(env, "PWD"));
    ft_update_env(env, "PWD", getcwd(cwd, sizeof(cwd)));
    register_pwd();
}

