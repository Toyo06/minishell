/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_prep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:53:48 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/05 22:47:07 by mayyildi         ###   ########.fr       */
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
