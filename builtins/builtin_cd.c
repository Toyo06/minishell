/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:38:15 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/09 22:33:20 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*find_break(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->next && tmp->next->data == 6)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

static void	update_path(t_list *tmp, t_env **env)
{
	if (tmp == NULL || tmp->data == 6)
		g_base.cd.path = ft_getenv(env, "HOME");
	else
		g_base.cd.path = tmp->arg;
}

void	handle_err(int err_code)
{
	err_msg_cd(err_code);
	if (g_base.retval.pcd == 1)
		exit(1);
}

static void	update_env_vars(t_env **env)
{
	char	cwd[2048];

	if (!ft_getenv(env, "PWD"))
		ft_update_env(env, "PWD", getcwd(cwd, sizeof(cwd)));
	ft_update_env(env, "OLDPWD", ft_getenv(env, "PWD"));
	ft_update_env(env, "PWD", getcwd(cwd, sizeof(cwd)));
}

void	ft_cd(t_list **lst, t_env **env)
{
	t_list	*tmp;

	if (ft_strcmp((*lst)->arg, CD_P) == 0)
		ft_cd_p(lst);
	else if (ft_strcmp((*lst)->arg, "cd") == 0)
	{
		tmp = find_break(lst);
		tmp = (*lst)->next;
		update_path(tmp, env);
		if (g_base.cd.path == NULL)
		{
			handle_err(7);
			return ;
		}
		if (chdir(g_base.cd.path) == -1)
		{
			handle_err(8);
			return ;
		}
		update_env_vars(env);
		register_pwd();
	}
}
