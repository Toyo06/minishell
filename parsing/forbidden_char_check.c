/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forbidden_char_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:29:55 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/11 22:21:05 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	countmallocnewstring(char *str)
{
	int		i;
	int		count;
	char	tmp;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|')
			count += 2;
		else if (str[i] == '"' || str[i] == '\'')
		{
			tmp = (str[i]);
			count++;
			i++;
			while (str[i] != tmp)
			{
				count++;
				i++;
			}
		}
		count++;
		i++;
	}
	return (count);
}

void	singlequotechecker(char *str)
{
	g_base.spaceoppipe.rtv[g_base.spaceoppipe.j]
		= str[g_base.spaceoppipe.i];
	g_base.spaceoppipe.j++;
	g_base.spaceoppipe.i++;
	while (str[g_base.spaceoppipe.i]
		&& str[g_base.spaceoppipe.i] != '\'')
	{
		g_base.spaceoppipe.rtv[g_base.spaceoppipe.j]
			= str[g_base.spaceoppipe.i];
		g_base.spaceoppipe.i++;
		g_base.spaceoppipe.j++;
	}
}

void	doublequotechecker(char *str)
{
	g_base.spaceoppipe.rtv[g_base.spaceoppipe.j] = str[g_base.spaceoppipe.i];
	g_base.spaceoppipe.j++;
	g_base.spaceoppipe.i++;
	while (str[g_base.spaceoppipe.i]
		&& str[g_base.spaceoppipe.i] != '"')
	{
		g_base.spaceoppipe.rtv[g_base.spaceoppipe.j]
			= str[g_base.spaceoppipe.i];
		g_base.spaceoppipe.i++;
		g_base.spaceoppipe.j++;
	}
}

int	errorset(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->data == 4 || tmp->data == 2 || tmp->data == 3
			|| tmp->data == 1 || tmp->data == 6)
			if (errorsetbis(&tmp) != 0)
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	errorsetbis(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	if (tmp->next == NULL)
	{
		if (tmp->data == 6)
			printf("minishell: syntax error near unexpected token `|'\n");
		else
			printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	else if (tmp->next->data != 10)
	{
		if (tmp->data == 6 && tmp->next->data == 6)
			printf("minishell: syntax error near unexpected token `|'\n");
		else
			printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
