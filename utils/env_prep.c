/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_prep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:53:48 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/01 13:20:29 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_prep(char **envp, t_env **env)
{
	int		i;
	char	**arr;

	i = 0;
	while (envp[i])
	{
		arr = ft_split(envp[i], '=');
		ft_update_env(env, arr[0], arr[1]);
		ft_free_arr(arr);
		i++;
	}
}

void	err_msg_pwd(int i)
{
	if (i == 10)
	{
		ft_putstr_fd("pwd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		if (g_base.retval.inp == 1)
			exit (1);
		g_base.retval.code = 1;
		return ;
	}
}
