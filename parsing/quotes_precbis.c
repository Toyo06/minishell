/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_precbis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 23:31:37 by sroggens          #+#    #+#             */
/*   Updated: 2023/04/14 23:31:38 by sroggens         ###   ########.fr       */
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
	while (str[g_base.rmquote.i])
	{
		if (str[g_base.rmquote.i] == '\'')
			new_str = addcoping(str, new_str);
		else if (str[g_base.rmquote.i] == '"')
			new_str = addcoping2(str, new_str);
		else
			new_str = addcoping3(str, new_str);
	}
	new_str[g_base.rmquote.j] = '\0';
	free(str);
	return (new_str);
}
