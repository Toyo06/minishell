/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_opcheck.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:08:40 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/26 14:12:13 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_base	g_base;

int	countmallocstr(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	setvalueforop();
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			if ((str[i + 1] == '<' && str[i] == '<')
				|| (str[i] == '>' && str[i + 1] == '>'))
				i++;
			count += 2;
		}
		i++;
	}
	return (ft_strlen(str) + count);
}

char	*addspace_be_foreop(char *str)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * (countmallocstr(str) + 1));
	while (str[g_base.op.i])
	{
		if (str[g_base.op.i] == '\'' || str[g_base.op.i] == '\"')
		{
			g_base.op.quote = str[g_base.op.i];
			new_str[g_base.op.j++] = str[g_base.op.i++];
			while (str[g_base.op.i] != g_base.op.quote)
				new_str[g_base.op.j++] = str[g_base.op.i++];
		}
		if (lexercheckcond(str))
		{
			new_str[g_base.op.j++] = ' ';
			new_str[g_base.op.j++] = str[g_base.op.i++];
			if ((str[g_base.op.i] == '>' && str[g_base.op.i - 1] == '>')
				|| (str[g_base.op.i] == '<' && str[g_base.op.i - 1] == '<'))
				new_str[g_base.op.j++] = str[g_base.op.i++];
			new_str[g_base.op.j++] = ' ';
		}
		else
			new_str[g_base.op.j++] = str[g_base.op.i++];
	}
	return (ft_strjoin(new_str, "\0"));
}

void	setvalueforop(void)
{
	g_base.op.i = 0;
	g_base.op.j = 0;
}

int	lexercheckcond(char	*str)
{
	if (str[g_base.op.i] == '|' || str[g_base.op.i] == '>'
		|| str[g_base.op.i] == '<')
		return (1);
	return (0);
}
