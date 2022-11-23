/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prepa_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:36:07 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/23 12:40:17 by sroggens         ###   ########.fr       */
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
