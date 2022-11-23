/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prepa_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:36:07 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/23 13:24:09 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_base	g_base;

void	ft_setenv(char **env)
{
	char	**tab_env;
	int	i;

	i = 0;
	tab_env = ft_split(env[0], '=');
	while (tab_env[i])
	{
		printf("%s\n", tab_env[i]);
		i++;
	}
}

void	prepaenv(char **envp, t_env **env)
{
	int	i;
	t_env	*tmp;
	char	**tab;

	i = 0;
	while (envp[i])
	{
		tab = ft_split(envp[i], '=');
		if ((*env) == NULL)
			addnodeenv(env, tab[0], tab[1]);
		else
		{
			addnodeenv(&tmp, tab[0], tab[1]);
			addnextnodeenv(env, tmp);
		}
		free(tab);
		i++;
	}
}
