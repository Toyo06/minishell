/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quote_detector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:08:10 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/19 00:57:08 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_base	g_base;
int	checkquote(char *str)
{
	int	i;

	i = 0;
	g_base.quote.doublequote = 0;
	g_base.quote.simplequote = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			g_base.quote.doublequote++;
		if (str[i] == '\'')
			g_base.quote.simplequote++;
		i++;
	}
	i = closeornot();
	return (i);
}

int	closeornot(void)
{
	if (g_base.quote.doublequote != (g_base.quote.doublequote / 2 * 2))
	{
		ft_printf("Quote not closed.\n");
		return (0);
	}
	if (g_base.quote.simplequote != (g_base.quote.simplequote / 2 * 2))
	{
		ft_printf("Simple quote not closed.\n");
		return (0);
	}
	return (1);
}
