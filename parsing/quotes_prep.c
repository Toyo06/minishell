/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_prep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:39:07 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 18:19:18 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prep_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			g_base.quote.nextquote = str[i];
			i++;
			while (str[i])
			{
				if (str[i] == g_base.quote.nextquote)
					break ;
				if (str[i] == ' ')
					str[i] = '\n';
				i++;
			}
		}
		i++;
	}
	return (str);
}

char	*revert_nl_to_sp(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = ' ';
		i++;
	}
	return (str);
}

char	**revert_quotes(char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i])
	{
		if (arr[i][j] == '\"' || arr[i][j] == '\'')
			arr[i] = revert_nl_to_sp(arr[i]);
		j++;
		if (arr[i][j] == '\0')
		{
			i++;
			j = 0;
		}
	}
	return (arr);
}

char	*rm_quote(char *str)
{
	char	*new_str;

	if (str == NULL)
		return (str);
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[g_base.rmquote.i] && str[g_base.rmquote.i] != 34
		&& str[g_base.rmquote.i] != 39)
	{
		new_str[g_base.rmquote.j] = str[g_base.rmquote.i];
		g_base.rmquote.i++;
		g_base.rmquote.j++;
	}
	sortrm(str);
	while (str[g_base.rmquote.i])
	{
		if (str[g_base.rmquote.i] != g_base.quote.nextquote)
		{
			new_str[g_base.rmquote.j] = str[g_base.rmquote.i];
			g_base.rmquote.j++;
		}
		g_base.rmquote.i++;
	}
	new_str[g_base.rmquote.j] = '\0';
	free(str);
	return (new_str);
}

void	sortrm(char *str)
{
	g_base.quote.nextquote = str[g_base.rmquote.i];
	if (str[g_base.rmquote.i] != '\0')
		g_base.rmquote.i++;
}
