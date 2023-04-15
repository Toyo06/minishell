/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotebis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:06:39 by sroggens          #+#    #+#             */
/*   Updated: 2023/04/15 14:19:07 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	countbefdol(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$')
		i++;
	return (i);
}

int	countmallocend(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '$')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
	i++;
	while (str[i])
	{
		i++;
		j++;
	}
	return (j);
}

int	countdolmal(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != '?')
		{
			i++;
			j++;
			while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"')
			{
				i++;
				j++;
			}
			return (j);
		}
		i++;
	}
	return (j);
}

char	*finalstringdol(char *str, t_env **env)
{
	char	*strnew;
	char	*tmpd;

	beforedol(str);
	replacedol(str);
	if (g_base.dol.strret != NULL)
		checkenvdol(env);
	afterdol(str);
	tmpd = ft_strjoin(g_base.dol.beforedol, g_base.dol.strret);
	strnew = ft_strjoin(tmpd, g_base.dol.end);
	free(str);
	if (strnew == NULL)
		return (NULL);
	return (strnew);
}
