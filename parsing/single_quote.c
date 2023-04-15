/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:45:06 by sroggens          #+#    #+#             */
/*   Updated: 2023/04/15 14:04:35 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*checkdol(char *str, t_env **env)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (str[i + 1] == '\0')
				return (str);
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] && str[i] == '$' && str[i + 1] != '?')
		{
			str = finalstringdol(str, env);
			i = 0;
			if (str == NULL)
				return (NULL);
		}
		else if (str[i] != '\0')
			i++;
	}
	return (str);
}

void	afterdol(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (countmallocend(str) > 0)
		g_base.dol.end = malloc(sizeof(char) * (countmallocend(str) + 1));
	while (str[i] != '$')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
	i++;
	if (str[i] == '\0')
	{
		g_base.dol.end = NULL;
		return ;
	}
	while (str[i])
	{
		g_base.dol.end[j] = str[i];
		i++;
		j++;
	}
	g_base.dol.end[j] = '\0';
}

void	beforedol(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (countbefdol(str) > 0)
		g_base.dol.beforedol = malloc(sizeof(char) * (countbefdol(str) + 1));
	while (str[i])
	{
		if (str[i] == '$')
			break ;
		g_base.dol.beforedol[j] = str[i];
		i++;
		j++;
	}
	if (countbefdol(str) > 0)
		g_base.dol.beforedol[j] = '\0';
	else
		g_base.dol.beforedol = NULL;
}

void	replacedol(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (countdolmal(str) > 0)
		g_base.dol.strret = malloc(sizeof(char) * (countdolmal(str) + 1));
	while (str[i] != '$')
		i++;
	if (str[i + 1] == '\0' || str[i + 1] == '\'')
	{
		free(g_base.dol.strret);
		g_base.dol.strret = NULL;
		return ;
	}
	i++;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
	{
		g_base.dol.strret[j] = str[i];
		i++;
		j++;
	}
	g_base.dol.strret[j] = '\0';
}

void	checkenvdol(t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	if (g_base.dol.strret == NULL)
		return ;
	while (tmp)
	{
		if (ft_strcmp(g_base.dol.strret, tmp->name) == 0)
		{
			free(g_base.dol.strret);
			g_base.dol.strret = ft_strdup(tmp->content);
			return ;
		}
		tmp = tmp->next;
	}
	free(g_base.dol.strret);
	g_base.dol.strret = NULL;
}
